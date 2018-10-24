import random
import sys

alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 "


if __name__ == "__main__":
    numEntries = 400
    filename = "TestTSV.tsv"
    if len(sys.argv) > 1:
        numEntries = int(sys.argv[1])

    if len(sys.argv) > 2:
        filename = sys.argv[2]

    defaultFields = ["First Name", "Last Name", "St. Address", "Postal Code"]
    with open(filename, 'w') as file:
        for name in defaultFields:
            file.write(name)
            file.write("\t")
        file.write("\n")
            
        for i in range(numEntries):
            for field in defaultFields:
                for character in range(random.randint(1,30)):
                    file.write(alphabet[random.randint(0, len(alphabet) - 1)])
                file.write("\t")
            file.write("\n")
