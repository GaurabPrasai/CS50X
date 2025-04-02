
input = input("Greeting: ")

input = input.strip().casefold()

if input.startswith('hello'):
    print("$0")

elif input.startswith('h'):
    print("$20")

else:
    print("$100")
