class Element:
    def __init__(self, x, y, prev):
        self.key = x
        self.element = y
        self.prev = prev
        self.next = None

    def get_key(self):
        return self.key


class LinkedMap:
    def __init__(self):
        self.arr = [[] for i in range(100000)]
        self.previous = None

    def get_position(self, x):
        k = 0
        for i in range(len(x)):
            k += (ord(x[i]) - ord('a') + 1) * (i + 1)
        return k % 100000

    def put(self, x, y):
        pos = self.get_position(x)
        for i in range(len(self.arr[pos])):
            if self.arr[pos][i].get_key() == x:
                self.arr[pos][i].element = y
                return
        a = Element(x, y, self.previous)
        self.previous = a
        if a.prev is not None:
            a.prev.next = a
        if not self.arr[pos]:
            self.arr[pos] = [a]
            return
        self.arr[pos].append(a)

    def exists(self, x):
        pos = self.get_position(x)
        if self.arr[pos]:
            for i in range(len(self.arr[pos])):
                if self.arr[pos][i].get_key() == x:
                    print(self.arr[pos][i].element, file=fileopen)
                    return
        print("none", file=fileopen)

    def delete(self, x):
        pos = self.get_position(x)
        if self.arr[pos]:
            for i in range(len(self.arr[pos])):
                if self.arr[pos][i].key == x:
                    moveprev = self.arr[pos][i].prev
                    movenext = self.arr[pos][i].next
                    if self.arr[pos][i].prev is not None:
                        self.arr[pos][i].prev.next = movenext

                    if self.arr[pos][i].next is not None:
                        self.arr[pos][i].next.prev = moveprev

                    if moveprev is None and movenext is None:
                        self.previous = None

                    if self.previous == self.arr[pos][i] and self.arr[pos][i] != None:
                        self.previous = moveprev

                    self.arr[pos].pop(i)
                    return

    def next_or_prev(self, x, s):
        posit = self.get_position(x)
        for i in range(len(self.arr[posit])):
            if s == 'prev':
                if self.arr[posit][i].key == x and self.arr[posit][i].prev != None:
                    print(self.arr[posit][i].prev.element, file=fileopen)
                    return
            else:
                if self.arr[posit][i].get_key() == x and self.arr[posit][i].next != None:
                    print(self.arr[posit][i].next.element, file=fileopen)
                    return
        print("none", file=fileopen)


with open('linkedmap.in', 'r') as fileopen:
    commands = fileopen.readlines()

with open('linkedmap.out', 'w') as fileopen:
    map = LinkedMap()
    for command in commands:
        command = command.strip().split()

        if command[0] == 'put':
            map.put(command[1], command[2])

        if command[0] == 'get':
            map.exists(command[1])

        if command[0] == 'delete':
            map.delete(command[1])

        if command[0] == 'prev':
            map.next_or_prev(command[1], 'prev')

        if command[0] == 'next':
            map.next_or_prev(command[1], 'next')