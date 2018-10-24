import random
import sys

alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 "


if __name__ == "__main__":
    numEntries = 400
    filename = "Testjson.json"
    if len(sys.argv) > 1:
        numEntries = int(sys.argv[1])

    if len(sys.argv) > 2:
        filename = sys.argv[2]

    defaultFields = ["First Name", "Last Name", "St. Address", "Postal Code"]
    allEntries = []
    for i in range(numEntries):
        entry = {}
        for field in defaultFields:
            for character in range(random.randint(1,30)):
                if field in entry:
                    entry[field] += alphabet[random.randint(0, len(alphabet) - 1)]
                else:
                    entry[field] = alphabet[random.randint(0, len(alphabet) - 1)]
        allEntries.append(entry)

    with open(filename, 'w') as json:
        json.write(str(allEntries).replace("'", "\"").replace(",", ",\n").replace("{", "{\n").replace("[", "[\n").replace("]", "]\n").replace("}", "}\n"))
            
