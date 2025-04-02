from pyfiglet import Figlet
from sys import argv

figlet = Figlet()
fonts = figlet.getFonts()

if len(argv) > 2:
    if argv[2] not in fonts:
        print("An Error Occured")
        exit(1)

if len(argv) == 2:
        print("An Error Occured")
        exit(1)

if len(argv) > 1 and (argv[1] != '-f' and argv[1] != '--font'):
        print("An Error Occured")
        exit(1)

s = input("Input: ")

if len(argv) == 1:
    # print(f"Output: ",{figlet.renderText(s)}, end="")
    print("Output:\n" + figlet.renderText(s), end="")

elif len(argv) == 3 and (argv[1] == "-f" or argv[1] == "--font"):
    figlet.setFont(font=argv[2])
    print("Output:\n" + figlet.renderText(s), end="")


