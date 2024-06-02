'''
To create ADT which implements set concepts.
a) Add(New Element) - Place a value into the set.
b) Remove (Element)
c) Contains (Element)
d) Size() - Returns number of elements
e) Intersection of two sets
f) Union of two sets
g) Difference of two sets
h) Subset
'''

s1 = set()
s2 = set()

def Create(a):
    n = int(input("Enter the number of elements in the set : "))
    for i in range(n):
        ele = int(input(f"Enter the element{i+1} : "))
        a.add(ele)
    print(f"Set(S1) : ",a)

def Add(a):
    ele = int(input("Enter the element that you want to insert : "))
    a.add(ele)
    print(a)

def Remove(a):
    ele = int(input("Enter the element that you want to remove : "))
    a.remove(ele)
    print(a)

def Presence(a):
    ele = int(input("Enter the element you want to check if it's present in the set : "))
    if ele in a:
        print(f"{ele} is present in the set")
    else :
        print(f"Element not found int the set")

def Size(a):
    print(f"Length of the set : {len(a)}")

def Intersection(a,b):
    i = a.intersection(b)
    print("The Intersection of set A and set B : ",i)

def Union(a,b):
    u = a.union(b)
    print("The Union of Set A and Set B : ",u)

def Difference(a,b):
    d = a.difference(b)
    print("The Difference of Set A and Set B : ",d)

def Subset(a,b):
    s = a.issubset(b)
    return s

print("\n\tENTER THE FIRST SET\t")
Create(s1)
print("\n\tENTER THE SECOND SET\t")
Create(s2)

b = True
while(b):
    print("\n----------    MENU    ----------")
    print("1. Add Element to the set")
    print("2. Remove element to the set")
    print("3. Check Presence of element in the set")
    print("4. Find length of the set")
    print("5. Perform Intersection on sets")
    print("6. Perform Union on sets")
    print("7. Perform Difference on sets")
    print("8. Find if set is subset of another set")
    print("9. Exit")
    choice1 = int(input("Enter your choice : "))

    if choice1 == 1 :
        print("1. Add element to first set")
        print("2. Add element to second set")
        choice2 = int(input("Enter your choice : "))
        if choice2 == 1 :
            Add(s1)
        elif choice2 == 2 :
            Add(s2)
        else:
            print("Invalid Input")

    elif choice1 == 2 :
        print("1. Remove element to first set")
        print("2. Remove element to second set")
        choice2 = int(input("Enter your choice : "))
        if choice2 == 1 :
            Remove(s1)
        elif choice2 == 2 :
            Remove(s2)
        else:
            print("Invalid Input")

    elif choice1 == 3 :
        print("1. Check Presence of element in first set")
        print("2. Check Presence of element in second set")
        choice2 = int(input("Enter your choice : "))
        if choice2 == 1 :
            Presence(s1)
        elif choice2 == 2 :
            Presence(s2)
        else:
            print("Invalid Input")

    elif choice1 == 4 :
        print("1. Find length of first set")
        print("2. Find length of second set")
        choice2 = int(input("Enter your choice : "))
        if choice2 == 1 :
            Size(s1)
        elif choice2 == 2 :
            Size(s2)
        else:
            print("Invalid Input")

    elif choice1 == 5 :
        Intersection(s1,s2)

    elif choice1 == 6 :
        Union(s1,s2)

    elif choice1 == 7 :
        print("1. Perform Set A - Set B")
        print("2. Perform Set B - Set A")
        choice2 = int(input("Enter your choice : "))
        if choice2 == 1 :
            Difference(s1,s2)
        elif choice2 == 2 :
            Difference(s2,s1)
        else:
            print("Invalid Input")

    elif choice1 == 8 :
        print("1. Check if Set A is Subset of Set B")
        print("2. Check if Set B is Subset of Set A")
        choice2 = int(input("Enter your choice : "))
        if choice2 == 1 :
            s = Subset(s1,s2)
            if s == 1 :
                print("Set A is subset of Set B")
            else : 
                print("Set A is not a subset of Set B")

        elif choice2 == 2 :
            s = Subset(s2,s1)
            if s == 1 :
                print("Set B is subset of Set A")
            else : 
                print("Set B is not a subset of Set A")

        else:
            print("Invalid Input")

    elif choice1 == 9 :
        b = False

    else :
        print("Invalid Choice")
