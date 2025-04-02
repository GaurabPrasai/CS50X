while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
        else:
            print("Invalid Height!")
    except ValueError:
        print("Not an Integer")


for i in range(height, 0, -1):
    for j in range(1, height + 1, 1):
        if j < i:
            print(" ", end="")
        else:
            print("#", end="")
    print()
