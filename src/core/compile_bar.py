from src.globals import ASYNC

# get the signal int to see when the program ends
import signal
import sys
import time

MAX = 100
MIN = 0
current = 0

from threading import Event

import math
import time

def exponential_decay_generator(current, base_sleep=0.01):
    b = 20
    x = current / MAX
    return base_sleep - (base_sleep * math.exp(-b * x))

@ASYNC
def show_bar(event: Event):
    global current
    while current < MAX and not event.is_set():
        current += 1
        print(f"\r[{'-'*current}{' '*((MAX-current)-1)}]", end="\r")
        time.sleep(0.03)
    if event.is_set():
        for _ in range(current, MAX):
            print(f"\r[{'-'*current}{' '*((MAX-current)-1)}]", end="\r")
            current += 1
            time.sleep(exponential_decay_generator(current, 0.01))
        return
        