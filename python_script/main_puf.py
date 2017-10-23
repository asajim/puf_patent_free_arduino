from __future__ import print_function
import glob
import pickle
import key
import puf_repetition

date = "171017B"
folder = "23LC1024/" + date + "/"
repetition = 128


# generate key
key = key.generate_key(10)
# or read key, saved in a file. 128 bits
# keyfile = "key"
# key = open(keyfile).read().replace('\n', '')


# file 1 as the basic for enrollment and generate helper data
file1 = folder + '1.c'
infile1 = puf_repetition.load_basefile(file1, repetition)

# generate helper data
helper_split = puf_repetition.generate_helper_data(key, infile1, repetition)

# save helper data
with open('helper', 'wb') as fp:
    pickle.dump(helper_split, fp)

# load helper data
# with open ('helper', 'rb') as fp:
#     helper_split = pickle.load(fp)


# verify the helper data
# for fl in glob.glob("23LC1024/" + date + "/" + "*.c"):
#     puf_repetition.verify_helper(fl, key, helper_split)
for fl in glob.glob("23LC1024/131017/*.c"):
    print(fl)
    puf_repetition.verify_helper(fl, key, helper_split, repetition)
print("------------------------------------")

for fl in glob.glob("23LC1024/171017B/*.c"):
    print(fl)
    puf_repetition.verify_helper(fl, key, helper_split, repetition)
print("------------------------------------")

for fl in glob.glob("23LC1024/171017C/*.c"):
    print(fl)
    puf_repetition.verify_helper(fl, key, helper_split, repetition)
print("------------------------------------")

for fl in glob.glob("23LC1024/171017D/*.c"):
    print(fl)
    puf_repetition.verify_helper(fl, key, helper_split, repetition)
print("------------------------------------")

for fl in glob.glob("23LC1024/171017E/*.c"):
    print(fl)
    puf_repetition.verify_helper(fl, key, helper_split, repetition)

