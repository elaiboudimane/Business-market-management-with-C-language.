import sys
import pickle

def get_parms():
    return pickle.load(open("init.dat","rb"))

if __name__ == "__main__":
    myparms = sys.argv[:]
    pickle.dump(myparms,open("init.dat","wb"))
