// file to plot the results
import matplotlib.pyplot as plt


def main():
        i = 0
        times_hopper_serial = []
        times_hoppers = []
        times_hopperw = []
        times_pollock_serial = []
        times_pollocks = []
        times_pollockw = []
        try:
            f = open("results.txt", "r")
        except IOError:
            print("File does not exist")
            exit(0)
        while i <= 5:
            line = f.readline()
            split = line.split()
            print(split)
            if len(split) == 0:
                i += 1
            for j in range(len(split)):
                split[j] = split[j].replace(",", "")
            try:
                if split[0] == "hopper" and i == 0:
                    num = float(split[2])
                    times_hopper_serial.append(num)
                elif split[0] == "hopper" and i == 1:
                    num = float(split[2])
                    times_hoppers.append(num)
                elif split[0] == "hopper" and i == 2:
                    num = float(split[2])
                    times_hopperw.append(num)
                elif split[0] == "pollock" and i == 3:
                    num = float(split[2])
                    times_pollock_serial.append(num)
                elif split[0] == "pollock" and i == 4:
                    num = float(split[2])
                    times_pollocks.append(num)
                elif split[0] == "pollock" and i == 5:
                    num = float(split[2])
                    times_pollockw.append(num)
            except:
                continue

        items = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
        threads = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
        threads_items = ["1/100", "2/200", "3/300", "4/400", "5/500", "6/600", "7/700", "8/800", "9/900",
                         "10/1000", "11/1100", "12/1200", "13/1300", "14/1400", "15/1500", "16/1600"]
        # serial, hopper
        plt.plot(items, times_hopper_serial)

        plt.xlabel("Items")
        plt.ylabel("time (in sec)")
        plt.title("Serial; p = hopper")

        plt.show()

        # parallel, strong-scaling, hopper
        plt.plot(threads, times_hoppers)

        plt.xlabel("Threads")
        plt.ylabel("time (in sec)")
        plt.title("Strong Scaling; platform = hopper, items = 1000")

        plt.show()

        # parallel, weak-scaling, hopper
        plt.plot(threads_items, times_hopperw)

        plt.xlabel("Threads/Items")
        plt.ylabel("time (in sec)")
        plt.xticks(["2/200", "4/400", "6/600", "8/800", "10/1000", "12/1200", "14/1400", "16/1600"])
        plt.title("Weak Scaling; platform = hopper")

        plt.show()

        # serial, pollock
        plt.plot(items, times_pollock_serial)

        plt.xlabel("Items")
        plt.ylabel("time (in sec)")
        plt.title("Serial; p = pollock")

        plt.show()

        # parallel, strong-scaling, pollock
        plt.plot(threads, times_pollocks)

        plt.xlabel("Threads")
        plt.ylabel("time (in sec)")
        plt.title("Strong Scaling; platform = pollock, items = 1000")

        plt.show()

        # parallel, weak-scaling, pollock
        plt.plot(threads_items, times_pollockw)

        plt.xlabel("Threads/Items")
        plt.xticks(["2/200", "4/400", "6/600", "8/800", "10/1000", "12/1200", "14/1400", "16/1600"])
        plt.ylabel("time (in sec)")
        plt.title("Weak Scaling; platform = pollock")

        plt.show()


if __name__ == "__main__":
        main()
