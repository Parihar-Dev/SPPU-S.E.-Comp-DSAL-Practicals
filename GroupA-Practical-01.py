'''
Consider Telephone book database of N clients. Make use of a hash table implementation to quickly look up
client's telephone number. Make use of two collision handling techniques and compare them using number of
comparisons required to find a set of telephone numbers.
'''

class Record :

    def __init__(self):
        self.name = None
        self.number = None

    def get_name(self):
        return self.name
    
    def get_number(self):
        return self.number
    
    def set_name(self,name):
        self.name = name

    def set_number(self,number):
        self.number = number

    def __str__(self):
        record = "Name : "+str(self.get_name())+"\tNumber : "+str(self.get_number())
        return record
    




class HashTable:

    def __init__(self):
        self.size = int(input("Enter the size of the table : "))
        self.table = list(None for i in range(self.size))
        self.elementscount = 0 
        self.comparisons = 0

    def isFull(self):
        if self.elementscount == self.size:
            return True
        return False
    
    def hash_function(self,element):
        return element % self.size
    
    def Linear_insert(self,record):
        if self.isFull():
            print("Hash Table is full , can't insert element")
            return False
        
        isStored = False
        position = self.hash_function(record.get_number())

        if (self.table[position] == None):
            self.table[position] = record
            print(f"Phone Number of {record.get_name()} is stored successfully at position {position}")
            isStored = True
            self.elementscount += 1

        else:
            print(f"Collision Occurs at position {position}, finding new position")
            while self.table[position] != None:
                position += 1
                if position >= self.size:
                    position = 0
            self.table[position] = record
            print(f"Phone Number of {record.get_name()} is stored successfully at position {position}")
            isStored = True
            self.elementscount += 1
        return isStored
    
    def Linear_Search(self,record):
        position = self.hash_function(record.get_number())
        isFound = False
        self.comparisons += 1
        if self.table[position] != None:
            if (self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                print(f"Record of {record.get_name()} is found at position {position} and total comparisons are {self.comparisons}")
                isFound = True
                return position
        
            else:
                position += 1
                if position >= self.size:
                    position = 0
                while self.table[position] != None and position <= self.size-1:
                    if(self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                        isFound = True
                        i = self.comparisons + 1
                        print(f"Record of {record.get_name()} is found at position {position} and total comparisons are {i}")
                        return position
                    
                    position += 1
                    if position>=self.size:
                        position = 0
                    self.comparisons += 1
            
        if isFound == False:
            print("Record not found")
            return False
    
    def display(self):
        for i in range(self.size):
            print(f"\nHash Value : {i} \t{self.table[i]}")
        print(f"The number of records in the table are {self.elementscount}")





class DoubleHash() :

    def __init__(self) :
        self.size = int(input("Enter the size of the Double Hash Table : "))
        self.table = list(None for i in range(self.size))
        self.elementcount = 0
        self.comparisons = 0

    def isFull(self) :
        if self.elementcount == self.size :
            return True
        return False
    
    def isPrime(self,num) :
        if num < 2 :
            return False
        for i in range(2,int(num**0.5)+1) :
            if num % i == 0 :
                return False
        return True
    
    def Largest_Prime_Less_Than(self,num) :
        for i in range(num,1,-1):
            if self.isPrime(i):
                return i
            
    def h1(self,element) :
        return element % self.size
    
    def h2(self,element) :
        prime = self.Largest_Prime_Less_Than(element)
        return prime - (element % prime)
    
    def Double_Hashing(self,record) :
        posFound = False
        i = 1
        while i <= self.size :
            newPosition = (self.h1(record.get_number()) + i*self.h2(record.get_number())) % self.size
            if self.table[newPosition] == None :
                posFound = True
                break
            else : 
                i += 1
        return posFound,newPosition
    
    def Double_Insert(self,record) :
        if self.isFull() :
            print("Hash Table is Full")
            return False
        posFound = False
        position = self.h1(record.get_number())

        if self.table[position] == None :
            self.table[position] = record
            print(f"Phone number of {record.get_name()} is stored successfully at {position}")
            posFound = True
            self.elementcount += 1
        else:
            print(f"Collision has occurred for {record.get_name()} at position {position} , Finding new position")
            while not posFound :
                posFound,position = self.Double_Hashing(record)
                if posFound :
                    self.table[position] = record
                    self.elementcount += 1
                    print(f"Phone number of {record.get_name()} is stored successfully at {position}")
            return posFound
        
    def Double_Search(self,record) :
        isfound = False
        position = self.h1(record.get_number())
        self.comparisons = 1

        if(self.table[position] != None) :
            if (self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                print(f"Phone Number of {record.get_name()} found at position {position} and total comparisons are {self.comparisons}")
                return position
            else:
                i = 1
                while i <= self.size :
                    position = (self.h1(record.get_number()) + i*self.h2(record.get_number())) % self.size
                    self.comparisons += 1
                    if (self.table[position] != None) :
                        if (self.table[position].get_name() == record.get_name() and self.table[position].get_number() == record.get_number()):
                            isfound = True
                            break
                    elif (self.table[position] == None) :
                        isfound = False
                        break
                    i += 1
        
        if isfound == True : 
            print(f"Record found at position {position} and total comparisons are {self.comparisons}")
        else :
            print("Record Not Found")
            return isfound
        
    def display(self):
        for i in range(self.size):
            print(f"Hash Value : {i} \t{self.table[i]}")
        print(f"The number of phone book records in the table are : {self.elementcount}")





def input_record():
    record = Record()
    name = input("Enter Name : ")
    number = int(input("Enter Number : "))
    record.set_name(name)
    record.set_number(number)
    return record


b = True
while(b):
    print("---------------    MENU    ---------------")
    print("1. Linear Probing")
    print("2. Double Probing")
    print("3. Exit")
    choice1 = int(input("Enter your choice : "))

    if choice1 == 1 :
        h1 = HashTable()
        choice2 = 0
        while choice2 != 4 :
            print("\n---- MENU ----")
            print("1. Insert")
            print("2. Search")
            print("3. Display")
            print("4. Back")
            choice2 = int(input("Enter your choice : "))

            if choice2 == 1 :
                record = input_record()
                h1.Linear_insert(record)

            elif choice2 == 2 :
                record = input_record()
                h1.Linear_Search(record)

            elif choice2 == 3 :
                h1.display()

            elif choice2 == 4 :
                break

            else:
                print("Invalid Input")

    elif choice1 == 2 :
        h2 = DoubleHash()
        choice2 = 0
        while choice2 != 4 :
            print("\n---- MENU ----")
            print("1. Insert")
            print("2. Search")
            print("3. Display")
            print("4. Back")
            choice2 = int(input("Enter your choice : "))

            if choice2 == 1 :
                record = input_record()
                h2.Double_Insert(record)

            elif choice2 == 2 :
                record = input_record()
                h2.Double_Search(record)

            elif choice2 == 3 :
                h2.display()

            elif choice2 == 4 :
                break

            else :
                print("Invalid Input")

    elif choice1 == 3 :
        b = False

    else :
        print("Invalid Input")
