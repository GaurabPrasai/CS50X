
number = int(input("Enter the number: "))

# Temporary variables
temp = number
originalNumber = number

isValid = True

# Calculate the checksum

i = 0
checksum = 0

while number != 0:

    digit = number % 10  # Get the rightmost digit

    if i % 2 != 0:  # Get the odd digits
        digit *= 2

        if digit > 9:
            digit -= 9
        checksum += digit

    if i % 2 == 0:  # Get the even digits
        checksum += digit

    number //= 10  # Remove the rightmost digits
    i += 1

if checksum % 10 != 0:
    isValid = False
    print("INVALID")

# Check the card length and starting digit
count = 0

while True:

    temp //= 10
    count += 1
    if temp == 0:
        break
    else:
        continue

# Find first two digits
firstTwoDigits = originalNumber

while firstTwoDigits >= 100:
    firstTwoDigits //= 10

# Check the card type and print it
if isValid:
    if (count == 15 and (firstTwoDigits == 34 or firstTwoDigits == 37)):
        print("AMEX")
    elif (count == 16 and (55 >= firstTwoDigits >= 51)):
        print("MASTERCARD")
    elif ((count == 13 or count == 16) and (49 >= firstTwoDigits >= 40)):
        print("VISA")
    else:
        print("INVALID")
