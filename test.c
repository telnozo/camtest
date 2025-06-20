//1. Paging: 

#include <stdio.h>

int main() {
    int page_size, num_pages;
    int page_table[50]; 
    int i;
    int page_number, offset;
    int frame_number, physical_address;

    printf("Enter the page size (in bytes): ");
    scanf("%d", &page_size);

    printf("Enter number of pages in page table: ");
    scanf("%d", &num_pages);

    printf("Enter frame number of each page (page 0 to page %d):\n", num_pages - 1);
    for (i = 0; i < num_pages; i++) {
        printf("Frame number for page %d: ", i);
        scanf("%d", &page_table[i]);
    }

    printf("Enter logical address (page number and offset): ");
    scanf("%d %d", &page_number, &offset);

    if (page_number < 0 || page_number >= num_pages) {
        printf("Invalid page number.\n");
        return 1;
    }

    if (offset < 0 || offset >= page_size) {
        printf("Invalid offset.\n");
        return 1;
    }

    frame_number = page_table[page_number];
    physical_address = (frame_number * page_size) + offset;

    printf("Frame Number = %d\n", frame_number);
    printf("Physical Address = %d\n", physical_address);

    return 0;
}
------------------------------------------------------------------------------------------------------
//2. FIFO

#include <stdio.h>

int fr[20], m; // frames array and number of frames

void display() {
    int i;  // declare loop variable at the top
    for(i = 0; i < m; i++)
        printf("%d\t", fr[i]);
    printf("\n");
}

int main() {
    int n, i, j;           // declare all variables at top
    int p[50];             // page references
    int pf = 0;            // page fault count
    int top = 0;           // pointer for FIFO replacement
    int flag1, flag2;
    float pr;

    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &m);

    // Initialize all frames as empty
    for(i = 0; i < m; i++) {
        fr[i] = -1;
    }

    printf("\nPage frames after each page request:\n");

    for(j = 0; j < n; j++) {
        flag1 = 0; // page found flag
        flag2 = 0; // empty frame found flag

        // Check if page is already in frames
        for(i = 0; i < m; i++) {
            if(fr[i] == p[j]) {
                flag1 = 1; // page hit
                break;
            }
        }

        // If page not found in frames
        if(flag1 == 0) {
            // Check if there is any empty frame
            for(i = 0; i < m; i++) {
                if(fr[i] == -1) {
                    fr[i] = p[j];
                    pf++;       // page fault occurs
                    flag2 = 1;  // page placed in empty frame
                    break;
                }
            }
        }

        // If page not found and no empty frame, replace page using FIFO
        if(flag1 == 0 && flag2 == 0) {
            fr[top] = p[j];
            top = (top + 1) % m; // circular increment of pointer
            pf++;                // page fault occurs
        }

        display();
    }

    printf("\nTotal Page Faults = %d\n", pf);
    pr = ((float)pf / n) * 100;
    printf("Page Fault Rate = %.2f%%\n", pr);

    return 0;
}
------------------------------------------------------------------------------------------------------------
//3. LRU

#include<stdio.h>
#include <math.h>
#include <stdbool.h>
bool checkinset(int x);


int MAX_CAP = 3;
int tmp_cap=3;
int n=0, i=0, j=0, k=0;
int set[3];


int main(){
	
	printf("Enter No. of Processes: ");
	scanf("%d", &n);
	int process[n];
	for(i=0; i<n; i++){
		scanf("%d", &process[i]);
	}
	
	int pgf=0; // initial no. of page faults

	for(i=0; i<MAX_CAP; i++){
		set[i]=-1;
	}
	
	for(i=0; i<n; i++){
		if(checkinset(process[i])){
			printf("already in set so, continued\n");
			continue;
		}else{
			if(tmp_cap>0){
				printf("initial set fill\n");
				set[i]=process[i];
				tmp_cap--;
			}else{
				printf("========================================>PAGE FAULT\n");
				pgf++;
				for(k=1; k<MAX_CAP; k++){
					set[k-1]=set[k];
				}
				set[MAX_CAP-1]=process[i];
			}
		}
		
	}
	printf("\nTotal Number of Page Faults in using LRU scheduling = %d\n", pgf);
	return 0;
}
bool checkinset(int x){
	printf("\ncheck for %d, set values: %d, %d, %d\n", x,set[0], set[1], set[2]);
	for(j=0; j<MAX_CAP; j++){
		if(set[j]==x) return true;
	}
	return false;
}
------------------------------------------------------------------------------------------------------
//4. Optimal Page Replacement

#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int p[50];   // reference string
    int fr[10];  // frames
    int pf = 0;  // page fault count
    int flag1, flag2;
    int index;
    float pr;

    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for(i = 0; i < m; i++)
        fr[i] = -1;  // initialize frames as empty

    for(i = 0; i < n; i++) {
        flag1 = 0;  // page found flag
        flag2 = 0;  // empty frame found flag

        // Check if page is already in frames
        for(j = 0; j < m; j++) {
            if(fr[j] == p[i]) {
                flag1 = 1;
                flag2 = 1;
                break;
            }
        }

        // If page not found in frames
        if(flag1 == 0) {
            // Check for empty frame
            for(j = 0; j < m; j++) {
                if(fr[j] == -1) {
                    fr[j] = p[i];
                    pf++;  // page fault
                    flag2 = 1;
                    break;
                }
            }
        }

        // If page not found and no empty frame, replace page optimally
        if(flag1 == 0 && flag2 == 0) {
            int farthest = i;
            index = -1;

            // Find the page in frames that will NOT be used for the longest time in future
            for(j = 0; j < m; j++) {
                int found = 0;
                for(k = i + 1; k < n; k++) {
                    if(fr[j] == p[k]) {
                        if(k > farthest) {
                            farthest = k;
                            index = j;
                        }
                        found = 1;
                        break;
                    }
                }
                // If page not found in future, this is best candidate to replace
                if(found == 0) {
                    index = j;
                    break;
                }
            }

            // Replace page at index
            fr[index] = p[i];
            pf++;
        }

        // Display current frames
        for(j = 0; j < m; j++)
            printf("%d\t", fr[j]);
        printf("\n");
    }

    printf("Number of page faults: %d\n", pf);
    pr = ((float)pf / n) * 100;
    printf("Page fault rate = %.2f%%\n", pr);

    return 0;
}
--------------------------------------------------------------------------------------------
//5. Contiguous Allocation 

#include <stdio.h>

#define SIZE 50

void displayBlocks(int files[]) {
    printf("\nBlock Allocation Status:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Block %2d : %s\n", i, files[i] == 1 ? "Allocated" : "Free");
    }
}

int main() {
    int files[SIZE] = {0}; // 0 = free, 1 = allocated
    int start, length, i, j, flag, n;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter starting block and length of file %d: ", i + 1);
        scanf("%d %d", &start, &length);

        if (start < 0 || start + length > SIZE) {
            printf("Invalid input: Block range out of bounds.\n");
            continue;
        }

        flag = 0;
        for (j = start; j < (start + length); j++) {
            if (files[j] == 1) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            for (j = start; j < (start + length); j++) {
                files[j] = 1;
            }
            printf("File %d allocated from block %d to %d.\n", i + 1, start, start + length - 1);
        } else {
            printf("File %d allocation failed. Blocks already allocated.\n", i + 1);
        }
    }

    displayBlocks(files); // Show block status after all allocations

    return 0;
}

-----------------------------------------------------------------------------------------------------
//6. Linked Allocation

#include <stdio.h>
#include <string.h>
#define SIZE 20

int disk[SIZE] = {0};           // 0=free, 1=allocated
int next[SIZE];                 // next block pointer
char files[SIZE][20] = {""};    // file names

void init() {
    for (int i = 0; i < SIZE; i++) {
        disk[i] = 0;
        files[i][0] = '\0';
        next[i] = -1;
    }
}

void allocate(char *name, int start, int end) {
    if (start < 0 || end >= SIZE || start > end) {
        printf("Invalid range\n");
        return;
    }
    
    int prev = -1;
    int first = -1;
    
    for (int i = start; i <= end; i++) {
        if (disk[i] == 0) {  // if block is free
            disk[i] = 1;
            strcpy(files[i], name);
            
            if (prev != -1) {
                next[prev] = i;
            } else {
                first = i;
            }
            prev = i;
        }
    }
    
    if (prev != -1) {
        printf("File '%s' allocated starting at block %d\n", name, first);
    } else {
        printf("No free blocks found\n");
    }
}

void show() {
    printf("\nDisk Status:\n");
    for (int i = 0; i < SIZE; i++) {
        if (disk[i] == 1) {
            printf("%2d: X %s -> %d\n", i, files[i], next[i]);
        } else {
            printf("%2d: .\n", i);
        }
    }
}

void showFile(char *name) {
    printf("Blocks for '%s': ", name);
    
    // Find first block
    int current = -1;
    for (int i = 0; i < SIZE; i++) {
        if (disk[i] == 1 && strcmp(files[i], name) == 0) {
            // Check if this is the first block
            int isFirst = 1;
            for (int j = 0; j < SIZE; j++) {
                if (next[j] == i) {
                    isFirst = 0;
                    break;
                }
            }
            if (isFirst == 1) {
                current = i;
                break;
            }
        }
    }
    
    // Follow chain
    while (current != -1) {
        printf("%d -> ", current);
        current = next[current];
    }
    printf("-1\n");
}

int main() {
    init();
    int choice;
    int start, end;
    char name[20];
    
    while (1) {
        printf("\n1. Allocate  2. Show Disk  3. Show File  4. Exit\n> ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            printf("File name: ");
            scanf("%s", name);
            printf("Start-End: ");
            scanf("%d %d", &start, &end);
            allocate(name, start, end);
        } else if (choice == 2) {
            show();
        } else if (choice == 3) {
            printf("File name: ");
            scanf("%s", name);
            showFile(name);
        } else if (choice == 4) {
            return 0;
        } else {
            printf("Invalid choice\n");
        }
    }
}

--------------------------------------------------------------------------------------------------
//7. Indexed Allocation

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

int main() {
    int memory[SIZE] = {0};  // 0 = free, 1 = allocated
    int indexBlock, n, i, count = 0;
    int allocatedBlocks[SIZE];
    char fileName[100]; // Input only, not shown

    printf("Enter the file name: ");
    scanf("%s", fileName);

    printf("Enter the index block: ");
    scanf("%d", &indexBlock);

    if (indexBlock < 0 || indexBlock >= SIZE) {
        printf("Invalid index block.\n");
        return 0;
    }

    if (memory[indexBlock] == 1) {
        printf("Index block already allocated.\n");
        return 0;
    }

    printf("Enter the number of blocks required: ");
    scanf("%d", &n);

    int freeCount = 0;
    for (i = 0; i < SIZE; i++) {
        if (memory[i] == 0 && i != indexBlock)
            freeCount++;
    }

    if (freeCount < n) {
        printf("Not enough free blocks.\n");
        return 0;
    }

    memory[indexBlock] = 1;
    for (i = 0; i < SIZE && count < n; i++) {
        if (memory[i] == 0 && i != indexBlock) {
            if (count == 0 || abs(allocatedBlocks[count - 1] - i) > 1) {
                allocatedBlocks[count++] = i;
                memory[i] = 1;
            }
        }
    }

    if (count < n) {
        printf("Couldn't find enough non-contiguous blocks.\n");
        return 0;
    }

    printf("Indexed File Allocation Successful!\n");
    printf("Block %d (Index): ", indexBlock);
    for (i = 0; i < n; i++) {
        printf("%d", allocatedBlocks[i]);
        if (i != n - 1)
            printf(", ");
    }
    printf(", -1\n");

    return 0;
}



//1)pipes:
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(){
    int fd[2];
    char msg[] = "hello";
    char buffer[20];
    pipe(fd);
    write(fd[1],msg,strlen(msg)+1);
    read(fd[0],buffer,sizeof(buffer));
    printf("read from the pipe:%s\n",buffer);
    return 0;
}


//2)FIFO:
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main(){
    int fd;
    char *fifopath = "type/myfifo";
    char writemsg[80] = "hello";
    char readmsg[80];

    
    mkfifo(fifopath, 0666);

   
    fd = open(fifopath, O_WRONLY);
    write(fd, writemsg, strlen(writemsg)+1);
    
    close(fd);

    fd = open(fifopath, O_RDONLY);
    read(fd, readmsg, sizeof(readmsg));
    printf("Received msg: %s\n", writemsg);
    close(fd);

    return 0;
}

//3)MESSAGE QUEUS:
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

// message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;
    int choice;

    // generate unique key
    key = ftok("progfile", 65);

    // create message queue and return id
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("1. Send msg\n2. Receive msg\nEnter choice: ");
    scanf("%d", &choice);
    getchar(); // consume leftover newline

    if (choice == 1) {
        message.msg_type = 1;
        printf("Enter message: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);

        // send message to queue
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        printf("Message sent: %s", message.msg_text);
    }
    else if (choice == 2) {
        // receive message from queue
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

        printf("Message received: %s", message.msg_text);

        // destroy the message queue
        msgctl(msgid, IPC_RMID, NULL);
        printf("Message queue deleted\n");
    }
    else {
        printf("Invalid choice\n");
    }

    return 0;
}


//4.)SHARED MEMORY

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

int main() {
    // generate unique key
    key_t key = ftok("shmfile", 65);

    // create shared memory segment of size 1024 bytes
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // attach to the shared memory
    char *str = (char*) shmat(shmid, (void*)0, 0);

    printf("Write to shared memory: ");
    fgets(str, 1024, stdin);

    printf("Data written in shared memory: %s", str);

    // detach from shared memory
    shmdt(str);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}