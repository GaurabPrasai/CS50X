import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
import datetime 
# Configure application
app = Flask(__name__)
# Custom filter
app.jinja_env.filters["usd"] = usd
=>

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # remember the user
    user_id = session["user_id"]

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[
        0]["cash"]
    rows = db.execute("select * from portfolio  where user_id = ?", user_id)

    total_value = 0
    for row in rows:
        row["price"] = lookup(row["symbol"])["price"]
        total_value += row["price"] * row["shares"]

    return render_template("index.html", transactions=rows, cash=cash,  total_cash=total_value + cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be an integer!")

        # handeling edge cases
        if symbol is None:
            return apology("Stock symbol doesn't exist")

        result = lookup(symbol)
        if result is None:
            return apology("Stock symbol doesn't exist")

        if shares <= 0:
            return apology("Enter a valid number!")

        # remember the user
        user_id = session["user_id"]

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[
            0]["cash"]

        final_cash = cash - shares * result["price"]

        if final_cash < 0:
            return apology("Not enough money!")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
                       final_cash, user_id)

        date = datetime.datetime.now()
        type = "buy"

        # update transaction in transaction database
        try:
            db.execute("INSERT INTO Transactions (user_id, symbol, shares, price, date, type) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, result["symbol"], shares, result["price"], date, type)
        except Exception as i:
            print(i)
            return apology("An error occured while inserting your cash into the database.")

        existing_shares = db.execute(
            "SELECT shares FROM Portfolio WHERE user_id = ? AND symbol = ?", user_id, result["symbol"])

        if existing_shares:
            db.execute("UPDATE Portfolio SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                       shares, user_id, result["symbol"])

        else:
            db.execute("INSERT INTO Portfolio (user_id, symbol, shares) VALUES (?, ?, ?)",
                       user_id, result["symbol"], shares)

        flash("Brought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, type, price, shares, date FROM Transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        price = request.form.get("price")
        result = lookup(symbol)

        if result is None:
            return apology("Stock symbol doesn't exist")

        return render_template("quoted.html", result=result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # validate the form data
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username or not password or not confirmation:
            return apology("Please enter both username and password correctly")

        if password != confirmation:
            return apology("Password doesn't match")

        # check if the username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("Username already exists")

        # generate the password hash
        password_hash = generate_password_hash(password)

        # insert new data into database
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)

            rows = db.execute(
                "SELECT id FROM users WHERE username = ?", username)
            session["user_id"] = rows[0]["id"]

            return redirect('/')
        except:
            return apology("Username already exists!")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol or lookup(symbol) is None:
            return apology("invalid symbol")
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:

                raise ValueError("shares can't be negative")
        except ValueError:
            return apology("invalid number of shares")
        price = lookup(symbol)["price"]

        holdings = db.execute(
            "select shares from portfolio where user_id = ? and  symbol = ?", user_id, symbol)[0]["shares"]

        if holdings < shares:
            return apology("Not enough shares!!")
        db.execute("update portfolio set shares = shares - ? where symbol = ? and user_id = ?",
                   shares, symbol, user_id)
        db.execute("insert into transactions (user_id, symbol, shares, price, type) VALUES(?, ?, ?, ?, ?)",
                   user_id, symbol, shares, price, "sell", )
        db.execute("update users set cash = cash + ? where id = ?",
                   shares * price, user_id)

        flash("Sold!")
        return redirect("/")
    else:
        stocks = db.execute(
            "SELECT symbol FROM Transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", stocks=stocks)

if __name__ == "__main__":
    app.run(debug=True)
