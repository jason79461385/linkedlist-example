#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// self-referential structure
struct listNode
{
	char data[16]; // each listNode contains a character
	struct listNode* nextPtr;
	// pointer to next node
}; // end structure listNode

typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode* ListNodePtr; // synonym for ListNode*
// prototypes
void insert(ListNodePtr* sPtr, char value[]);
char deleted(ListNodePtr* sPtr, char value[]);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);
int main(void)
{
	ListNodePtr startPtr = NULL; // initially there are no nodes
	unsigned int choice; // user's choice
	// char entered by user
	char a[16];
	
	
	instructions(); // display the menu
	printf("%s", "? ");
	scanf("%u", &choice);
	
	
		while (choice != 3)
		{
			switch (choice)
			{
			case 1:
				printf("%s", "Please enter a word (less than or equal to 15 letters): ");

				scanf("\n%15s", a);
				insert(&startPtr, a); // insert item in list
				printList(startPtr);
				
				break;
			case 2: // delete an element
			// if list is not empty
				if (!isEmpty(startPtr))
				{
					printf("%s", "Enter a word to be deleted: ");

					scanf("\n%15s", a);
					// if character is found, remove it
					if (deleted(&startPtr, a)) { // remove item
						printf("%15s deleted.\n", a);
						printList(startPtr);
					} // end if
					else
					{
						printf("%15s not found.\n\n", a);
					} // end else

				} // end if
				else
				{
					puts("List is empty.\n");
				} // end else
				break;
				default:
						puts("Invalid choice.\n");
						instructions();
						break;
			} // end switch

			printf("%s", "? ");
			scanf("%u", &choice);
		} // end while
	
	puts("End of run.");
	
	
	system("pause");
	return 0;
} // end main
void instructions(void)
{
	puts("Enter your choice:\n"
		" 1 to insert an element into the list.\n"
		" 2 to delete an element from the list.\n"
		" 3 to end.");
} // end function instructions
// insert a new value into the list in sorted order
void insert(ListNodePtr* sPtr, char value[])
{
	ListNodePtr newPtr = { NULL }; // pointer to new node
	ListNodePtr previousPtr = NULL; // pointer to previous node in list
	ListNodePtr currentPtr = NULL; // pointer to current node in list 
	newPtr = (ListNode*)malloc(sizeof(ListNode)); // create node
	if (newPtr != NULL) { // is space available
		strncpy(newPtr->data,value,15); // place value in node
		
		newPtr->nextPtr = NULL; // node does not link to another node
		previousPtr = NULL;
		currentPtr = *sPtr;
		// loop to find the correct location in the list
		while (currentPtr != NULL && strlen(currentPtr->data) >= strlen(value)) {
			previousPtr = currentPtr; // walk to ...
			currentPtr = currentPtr->nextPtr; // ... next node
		} // end while
		if
			(previousPtr == NULL)
		{
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		} // end if
		else { // insert new node between previousPtr and currentPtr
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		} // end else
	} // end if
	else
	{
		printf("%s not inserted. No memory available.\n", value);
	} // end else
} // end function insert
char deleted(ListNodePtr* sPtr, char value[]) {
	ListNodePtr previousPtr; // pointer to previous node in list
	ListNodePtr currentPtr; // pointer to current node in list
	ListNodePtr tempPtr; // temporary node pointer
	// delete first node
	
	if(strcmp (value , (*sPtr)->data )==0) {
		tempPtr = *sPtr; // hold onto node being removed 
		*sPtr = (*sPtr)->nextPtr; // de-thread the node
		free(tempPtr); // free the de-threaded node
		return *value;
	} // end if
	else
	{
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextPtr;
		
		while(currentPtr != NULL && strcmp(currentPtr->data,value)!=0) {
			previousPtr = currentPtr; // walk to ...
			currentPtr = currentPtr->nextPtr; // ... next node
		} // end while
		// delete node at currentPtr
		if(currentPtr != NULL) {
			tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			free(tempPtr);
			return *value;
		} // end if
	} // end else
	return'\0';
} // end function delete
int isEmpty(ListNodePtr sPtr)
{
	return sPtr == NULL;
} // end function isEmpty
// print the list
void printList(ListNodePtr currentPtr)
{
	// if list is empty
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	} // end if
	else {
		puts("The list is:");
		// while not the end of the list
		while
			(currentPtr != NULL) {
			printf("%15s --> ", currentPtr->data);
			currentPtr = currentPtr->nextPtr;
		} // end while
		puts("NULL\n");
	} // end else
} // end function printList
