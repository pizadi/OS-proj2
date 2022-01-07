import threading, random, os
fd = os.open('/dev/bank', os.O_WRONLY)
data = os.read(fd, 128)
def func():
    for i in range(1000000):
        os.write(f'e,{random.randint(1, 99)},0,1')
t1 = threading.Thread(target=func)
t2 = threading.Thread(target=func)
os.write(f'r')
t1.start()
t2.start()

t1.join()
t2.join()

os.close(fd)