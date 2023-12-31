#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
  int data;
  struct node *next;
};

struct BigInteger
{
  int length;
  struct node *L;
};

struct node *createNode (int data)
{
  struct node *newNode = (struct node *) malloc (sizeof (struct node));
  if (newNode)
    {
      newNode->data = data;
      newNode->next = NULL;
    }
  return newNode;
}

struct BigInteger initialize (char *s)
{
  struct BigInteger value;
  value.length = 0;
  value.L = NULL;
  int len = strlen (s);
  int i = 0;
  for (i=0; i < len; i++)
    {
      if (s[i] < '0' || s[i] > '9')
	{
	  printf ("Invalid .\n");
	  exit (1);
	}
      int digit = s[i] - '0';
      struct node *newNode = createNode (digit);
      if (!newNode)
	{
	  printf ("Memory allocation failed.\n");
	  exit (1);
	}
      newNode->next = value.L;
      value.L = newNode;
      value.length++;
    }
  if (value.length == 0)
    {
      value.length = 1;
      value.L = createNode (0);
    }

  return value;
}

//add two BigIntegers
struct BigInteger add (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger result;
  result.length = 0;
  result.L = NULL;

  int carry = 0, sum = 0;
  struct node *ptr1 = a.L;
  struct node *ptr2 = b.L;
  while (ptr1 || ptr2 || carry)
    {
      sum = carry;
      if (ptr1)
	{
	  sum += ptr1->data;
	  ptr1 = ptr1->next;
	}
      if (ptr2)
	{
	  sum += ptr2->data;
	  ptr2 = ptr2->next;
	}
      carry = sum / 10;
      struct node *newNode = createNode (sum % 10);
      if (result.L == NULL)
	{
	  result.L = newNode;
	}
      else
	{
	  struct node *temp = result.L;
	  while (temp->next)
	    {
	      temp = temp->next;
	    }
	  temp->next = newNode;
	}

      result.length++;
    }
  return result;
}

//subtract two BigIntegers
struct BigInteger sub (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger result;
  result.length = 0;
  result.L = NULL;

  int borrow = 0, difference = 0;
  struct node *ptr1 = a.L;
  struct node *ptr2 = b.L;
  while (ptr1 || ptr2)
    {
      difference = borrow;

      if (ptr1)
	{
	  difference += ptr1->data;
	  ptr1 = ptr1->next;
	}
      if (ptr2)
	{
	  difference -= ptr2->data;
	  ptr2 = ptr2->next;
	}
      if (difference < 0)
	{
	  difference += 10;
	  borrow = -1;
	}
      else
	borrow = 0;

      struct node *newNode = createNode (difference);
      if (result.L == NULL)
	{
	  result.L = newNode;
	}
      else
	{
	  struct node *temp = result.L;
	  while (temp->next)
	    {
	      temp = temp->next;
	    }
	  temp->next = newNode;
	}

      result.length++;
    }
  struct node *temp = result.L;
  struct node *last = NULL;
  while (temp)
    {
      if (temp->data != 0)
	{
	  last = temp;
	}
      temp = temp->next;
    }

  if (last)
    {
      last->next = NULL;
    }
  else
    {
      result.L = createNode (0);
    }
  return result;
}

//multiply two BigIntegers
struct BigInteger mul (struct BigInteger a, struct BigInteger b)
{
  struct BigInteger result;
  result.length = 1;
  result.L = createNode (0);

  struct node *ptr2 = b.L;
  int position = 0;	

  while (ptr2)
    {
      int value = ptr2->data;
      struct BigInteger product;
      product.length = 0;
      product.L = NULL;
      struct node *ptr1 = a.L;
      int carry = 0;

      while (ptr1)
	{
	  int total = (ptr1->data * value) + carry;
	  carry = total / 10;
	  struct node *newNode = createNode (total % 10);

	  if (product.L == NULL)
	    {
	      product.L = newNode;
	    }
	  else
	    {
	      struct node *temp = product.L;
	      while (temp->next)
		{
		  temp = temp->next;
		}
	      temp->next = newNode;
	    }

	  ptr1 = ptr1->next;
	}

      if (carry > 0)
	{
	  struct node *newNode = createNode (carry);
	  if (product.L == NULL)
	    {
	      product.L = newNode;
	    }
	  else
	    {
	      struct node *temp = product.L;
	      while (temp->next)
		{
		  temp = temp->next;
		}
	      temp->next = newNode;
	    }
	}
      for (int i = 0; i < position; i++)
	{
	  struct node *zero = createNode (0);
	  zero->next = product.L;
	  product.L = zero;
	}

      // Add the product to the result
      result = add (result, product);

      ptr2 = ptr2->next;
      position++;
    }

  return result;
}

struct node* reverseList(struct node* head) {
    struct node* prev = NULL;
    struct node* temp = head;
    struct node* next = NULL;
    while (temp != NULL) {
        next = temp->next;
        temp->next = prev;
        prev = temp;
        temp = next;
    }
    return prev; 
}

struct node* copyList(struct node* head) {
    struct node* headNew = NULL;
    struct node* temp = head;
    struct node* tail = NULL;

    while (temp != NULL) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = temp->data;
        newNode->next = NULL;

        if (tail == NULL) {
            headNew = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        temp = temp->next;
    }

    return headNew;
}

int compare(struct BigInteger num1, struct BigInteger num2) 
{
    struct node* ptr1 = num1.L;
    struct node* ptr2 = num2.L;
    int length1 = 0;
    int length2 = 0;

    while (ptr1 != NULL)
    {
        length1++;
        ptr1 = ptr1->next;
    }

    while (ptr2 != NULL) 
    {
        length2++;
        ptr2 = ptr2->next;
    }

    if (length1 < length2) 
        return -1;
    else if (length1 > length2) 
        return 1;
    else 
    {
        struct node* rev1 = copyList(num1.L);
        ptr1 = reverseList(rev1);;
        
        struct node* rev2 = copyList(num2.L);
        ptr2 = reverseList(rev2); 
        while (ptr1 != NULL) {
            if (ptr1->data < ptr2->data) 
            {
                free(rev1);  
                free(rev2); 
                return -1;
            } 
            else if (ptr1->data > ptr2->data) 
            {
                free(rev1);  
                free(rev2); 
                return 1;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        free(rev1);
        free(rev2);
        return 0; 
    }
}

// Function to divide two BigIntegers(returning quotient)
struct BigInteger div1(struct BigInteger dividend, struct BigInteger divisor) 
{
  struct BigInteger quotient;
  quotient.length = 1;
  quotient.L = createNode(0);

  struct BigInteger first;
  first.length = 1;
  first.L = createNode(1);

  struct BigInteger zero;
  zero.length = 1;
  zero.L = createNode(0);

  if (compare(divisor, zero) == 0) {
    printf("Error.\n");
    exit(1);
  }

  if (compare(dividend, zero) == 0) {
    return zero;
  }

  struct BigInteger rem = dividend;

  while (compare(rem, divisor) >= 0) 
  {
    rem = sub(rem, divisor);
    quotient = add(quotient, first);
  }

  return quotient;
}

// divide two BigIntegers (returning rem)
struct BigInteger mod (struct BigInteger D, struct BigInteger divisor)
{
  struct BigInteger zero;
  zero.length = 1;
  zero.L = createNode (0);

  if (compare (divisor, zero) == 0)
    {
      printf ("Error: Division by zero.\n");
      exit (1);
    }

  struct BigInteger rem = D;

  while (compare (rem, divisor)>=0)
      rem = sub (rem, divisor);

  return rem;
}

void Reverse (struct node *temp)
{
  if (temp == NULL)
    {
      return;
    }
  Reverse (temp->next);
  printf ("%d", temp->data);
}

// Function to display a BigInteger in reverse order
void display (struct BigInteger num)
{
  if (num.length == 0)
    {
      printf ("0\n");
      return;
    }

  Reverse (num.L);	
  printf ("\n");
}
