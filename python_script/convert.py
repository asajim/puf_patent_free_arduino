import glob, os, re

scale = 16
num_of_bits = 8


def convert_file_hex_to_bin(name):
    f = open(name).readlines()
    f = [x.strip() for x in f]
    convert = []
    for a in f:
        convert.append(bin(int(a, scale))[2:].zfill(num_of_bits))
    result = ""
    i = 1;
    for a in convert:
        for b in a:
            result += b + " "
        if i % 4 == 0:
            result += "\n"
        i += 1
    return result

def convert_folder(folder):
    os.chdir(folder + "/")
    for fl in glob.glob("*"):
        if fl.endswith(".c"):
            os.remove(fl)

    for fl in glob.glob("*"):
        name = fl.split('.')[0]
        f = open(name + ".c", "w+")
        # # print file
        converted = convert_file_hex_to_bin(fl)
        # print converted
        f.seek(0)
        f.write(converted)
        f.truncate()
        f.close()

    os.chdir("..")

os.chdir("23LC1024/")
# convert_folder('A')
# convert_folder('B')
# convert_folder('C')
# convert_folder('D')
# convert_folder('E')
# convert_folder('F')
# convert_folder('G')
# convert_folder('H')
# convert_folder('I')
# convert_folder('J')
# convert_folder('K')
# convert_folder('L')
# convert_folder('M')
# convert_folder('N')
# convert_folder('O')
# convert_folder('P')
# convert_folder('Q')
# convert_folder('R')
convert_folder('S')
convert_folder('T')
convert_folder('U')
convert_folder('V')
convert_folder('W')
