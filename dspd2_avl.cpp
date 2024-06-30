#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define MAX_PLS 20 // assuming maximum no of playlists we can create is 20
#define MAX_FIELD_LENGTH 100
#define MAX_LINE_LENGTH 100
 
typedef struct TreeNode {
    char singer[50];
    char lyricist[50];
    char film[50];
    char composer[50];
    char genre[50];
    char songName[50];
    int duration;
    int height;
    int serialNumber;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

static int dataBaseCount = 0;

void playSong(TreeNode *sptr){
	printf("Song No : %d\n", sptr->serialNumber);
    printf("Song: %s\n", sptr->songName);
    printf("Singer: %s\n", sptr->singer);
    printf("Lyricist: %s\n", sptr->lyricist);
    printf("Film/Album: %s\n", sptr->film);
    printf("Composer: %s\n", sptr->composer);
    printf("Genre: %s\n", sptr->genre);
    printf("Duration: %d\n\n", sptr->duration);
}


int max(int a, int b)
{
    int ret_val;
    if(a>b){
    	ret_val=a;
	}
	else{
		ret_val=b;
	}
	return ret_val;
}


int Height(TreeNode* root)
{
	int ret_val;
    if (root == NULL)
	{
        return -1;
    }
    else if(!root->left && !root->right)
    {
    	return 0;
	}
    int leftsub_height = Height(root->left);
    int rightsub_height = Height(root->right);
   	
	return max(leftsub_height,rightsub_height)+1;
}


TreeNode* LeftRotate(TreeNode* root) 
{
    TreeNode* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    temp->height = max(Height(temp->left), Height(temp->right)) + 1;
    return temp;
}

TreeNode* RightRotate(TreeNode* root) 
{
    TreeNode* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(Height(root->left), Height(root->right)) + 1;
    temp->height = max(Height(temp->left), Height(temp->right)) + 1;
    return temp;
}

int BalanceFactor(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }

    return Height(node->left) - Height(node->right);
}



TreeNode* InsertHelper(TreeNode* root, TreeNode* newSong) 
{
    
    if (root == NULL) 
	{
        root = newSong;
        return root;
    }

    
    if (strcmp(newSong->songName, root->songName) < 0) 
	{
        root->left = InsertHelper(root->left, newSong);
    }
    
    else if (strcmp(newSong->songName, root->songName) > 0) 
	{
        root->right = InsertHelper(root->right, newSong);
    }
   
    else
	{
        free(newSong);
        return root;
    }

    
    root->height = max(Height(root->left), Height(root->right)) + 1;

   
    int balanceFactor = BalanceFactor(root);

    
    if (balanceFactor > 1 && strcmp(newSong->songName, root->left->songName) < 0) 
	{
       
        return RightRotate(root);
    }
    else if (balanceFactor > 1 && strcmp(newSong->songName, root->left->songName) > 0) 
	{
        
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    else if (balanceFactor < -1 && strcmp(newSong->songName, root->right->songName) > 0) 
	{
        
        return LeftRotate(root);
    }
    else if (balanceFactor < -1 && strcmp(newSong->songName, root->right->songName) < 0) 
	{
       
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

//insert song function
void InsertSongFromFile(TreeNode** root, FILE* fileptr) 
{
    char line[MAX_FIELD_LENGTH];
    if (fgets(line, MAX_FIELD_LENGTH, fileptr) == NULL) return;
    line[strcspn(line, "\r\n")] = '\0'; // remove newline characters from the line

    TreeNode* newSong = (TreeNode*) malloc(sizeof(TreeNode));
    dataBaseCount++;

    sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d", newSong->songName, newSong->singer, newSong->lyricist, newSong->film, newSong->composer, newSong->genre, &newSong->duration);

    newSong->height = 1;
    newSong->left = NULL;
    newSong->right = NULL;

    *root = InsertHelper(*root, newSong);

    printf("Song added to the library: %s\n", newSong->songName);
}

//display songs in the tree by inorder traversal
void PrintSongs(TreeNode* root) 
{
    if (root) 
	{
        printf("Song: %s\n", root->songName);
        printf("Singer: %s\n", root->singer);
        printf("Lyricist: %s\n", root->lyricist);
        printf("Film/Album: %s\n", root->film);
        printf("Composer: %s\n", root->composer);
        printf("Genre: %s\n", root->genre);
        printf("Duration: %d seconds\n\n", root->duration);
    }
}


//q3
void PrintInAscendingOrder(TreeNode* root) 
{
    if (root == NULL) 
	{
        return;
    }

    PrintInAscendingOrder(root->left);
    printf("Song Name: %s\n", root->songName);
    printf("Singer: %s\n", root->singer);
    printf("Lyricist: %s\n", root->lyricist);
    printf("Film/Album: %s\n", root->film);
    printf("Composer: %s\n", root->composer);
    printf("Genre: %s\n", root->genre);
    printf("Duration: %d seconds\n\n", root->duration);
    PrintInAscendingOrder(root->right);
}

//helper to print in descending order
void DescendingOrder(TreeNode* root) 
{
    if (root == NULL) 
	{
        return;
    }

    DescendingOrder(root->right);
    printf("Song Name: %s\n", root->songName);
    printf("Singer: %s\n", root->singer);
    printf("Lyricist: %s\n", root->lyricist);
    printf("Film/Album: %s\n", root->film);
    printf("Composer: %s\n", root->composer);
    printf("Genre: %s\n", root->genre);
    printf("Duration: %d seconds\n\n", root->duration);
    DescendingOrder(root->left);
}

//q2 handled in insert song function itself i.e. removeDuplicates() function

//question 3
void PrintPlaylistinAscendingDescending(TreeNode* root) 
{
    printf("Printing playlist in ascending order:\n");
    PrintInAscendingOrder(root);

    printf("Printing playlist in descending order:\n");
    DescendingOrder(root);
}


//q4 need to be seen
// Function to delete a node with given song name and artist and balance the AVL tree
TreeNode* findMinNode(TreeNode* node) 
{
    if (node == NULL)
        return NULL;

    if (node->left != NULL)
        return findMinNode(node->left);
    else
        return node;
}

void deleteNode(TreeNode** root, char* songName, char* artist) {
    if (*root == NULL) {
        return;
    }

    
    if (strcmp((*root)->songName, songName) == 0 && strcmp((*root)->singer, artist) == 0) {
        TreeNode* temp = NULL;
        if ((*root)->left == NULL) {
            temp = *root;
            *root = (*root)->right;
            free(temp);
        } else if ((*root)->right == NULL) {
            temp = *root;
            *root = (*root)->left;
            free(temp);
        } else {
            temp = findMinNode((*root)->right);
            strcpy((*root)->songName, temp->songName);
            strcpy((*root)->singer, temp->singer);
            strcpy((*root)->lyricist, temp->lyricist);
            strcpy((*root)->film, temp->film);
            strcpy((*root)->composer, temp->composer);
            strcpy((*root)->genre, temp->genre);
            (*root)->duration = temp->duration;
            deleteNode(&(*root)->right, temp->songName, temp->singer);
        }
    }
    
    else if (strcmp(songName, (*root)->songName) < 0) {
        deleteNode(&(*root)->left, songName, artist);
    }
    
    else if (strcmp(songName, (*root)->songName) > 0) {
        deleteNode(&(*root)->right, songName, artist);
    }
   
    else {
        deleteNode(&(*root)->left, songName, artist);
        deleteNode(&(*root)->right, songName, artist);
    }
    
   
    int balance = BalanceFactor(*root);
    if (balance > 1 && BalanceFactor((*root)->left) >= 0) {
        *root = RightRotate(*root);
    } else if (balance < -1 && BalanceFactor((*root)->right) <= 0) {
        *root = LeftRotate(*root);
    } else if (balance > 1 && BalanceFactor((*root)->left) < 0) {
        (*root)->left = LeftRotate((*root)->left);
        *root = RightRotate(*root);
    } else if (balance < -1 && BalanceFactor((*root)->right) > 0) {
        (*root)->right = RightRotate((*root)->right);
        *root = LeftRotate(*root);
    }
}



//q5
int countMatches(TreeNode *root, int num_attributes, char **attributes, char **values){
    int matches = 0, i;
    for (i = 0; i < num_attributes; i++) {
        if (strcmp(attributes[i], "singer") == 0 && strcmp(root->singer, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "lyricist") == 0 && strcmp(root->lyricist, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "film") == 0 && strcmp(root->film, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "composer") == 0 && strcmp(root->composer, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "genre") == 0 && strcmp(root->genre, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "songName") == 0 && strcmp(root->songName, values[i]) == 0) {
            matches++;
        }
        else if (strcmp(attributes[i], "duration") == 0 && root->duration == atoi(values[i])) {
            matches++;
        }
    }
    return matches;
}

void CreatePlaylistHelper(TreeNode* root, char* attributes[], char* values[], int num_attributes, TreeNode** playlist) {
	int i=1;
    if (root == NULL) 
	{
        return;
    }

    int matches = countMatches(root, num_attributes, attributes, values);
    if (matches == num_attributes) 
	{
        TreeNode *new_song = (TreeNode*)malloc(sizeof(TreeNode));
        new_song->serialNumber=i;
        strcpy(new_song->singer, root->singer);
        strcpy(new_song->lyricist, root->lyricist);
        strcpy(new_song->film, root->film);
        strcpy(new_song->composer, root->composer);
        strcpy(new_song->genre, root->genre);
        strcpy(new_song->songName, root->songName);
        new_song->duration = root->duration;
        new_song->left = NULL;
        new_song->right = NULL;
        *playlist=InsertHelper(*playlist, new_song);
        i++;
    }

    CreatePlaylistHelper(root->left, attributes, values, num_attributes, playlist);
    CreatePlaylistHelper(root->right, attributes, values, num_attributes, playlist);
}

TreeNode* CreatePlaylist(TreeNode *root, char* attributes[], char* values[], int num_attributes) 
{
    TreeNode *playlist = NULL;
    CreatePlaylistHelper(root, attributes, values, num_attributes, &playlist);
    return playlist;
}



//q6
void insertSerialNumber(TreeNode* root)
{
    static int serialNumber = 1;
    if (root != NULL) {
        insertSerialNumber(root->left);
        root->serialNumber = serialNumber++;
        insertSerialNumber(root->right);
    }
}

//void printInorder(TreeNode* root, int* count)
//{
//    if (root != NULL)
//    {
//        printInorder(root->left, count);
//        printf("%d\t\t%s\n", (*count)++, root->songName);
//        printInorder(root->right, count);
//    }
//}
void printInorder(TreeNode* root, int* count)
{
    if (root != NULL)
    {
        printInorder(root->left, count);
        printf("%d\t\t%s\n", root->serialNumber, root->songName);
        printInorder(root->right, count);
    }
}
TreeNode* findNode(TreeNode* root, int s_no) {
    if (root == NULL) {
        return NULL;
    }

    if (root->serialNumber == s_no) {
        return root;
    }

    TreeNode* leftResult = findNode(root->left, s_no);
    if (leftResult != NULL) {
        return leftResult;
    }

    TreeNode* rightResult = findNode(root->right, s_no);
    if (rightResult != NULL) {
        return rightResult;
    }

    return NULL;
}

void displayPlaylist(TreeNode* root)
{
    if (root == NULL)
    {
        printf("Playlist is empty!\n");
        return;
    }
    int count = 1; 
    printInorder(root, &count); 

    
    int sNo;
    printf("\nEnter the serial number of the song to display the details of that particular song\n");
    scanf("%d",&sNo);
    
	TreeNode* curr_song= findNode(root,sNo);
			printf("*****Details of the current song*****\n");
			printf("Song Name: %s\n", curr_song->songName);
            printf("Singer: %s\n", curr_song->singer);
            printf("Lyricist: %s\n", curr_song->lyricist);
            printf("Film/Album: %s\n", curr_song->film);
            printf("Composer: %s\n", curr_song->composer);
            printf("Genre: %s\n", curr_song->genre);
            printf("Duration: %d seconds\n\n", curr_song->duration);

	
    
    int key;
    printf("enter 1 to display details of the previous song\nEnter 2 to display the details of the next song\n\nEnter the index\n\n");
    scanf("%d",&key);
    if(key==1){
    	TreeNode* prev_song=findNode(root,sNo-1);    
      	if(!prev_song){
    		printf("Previous song details cannot be displayed\n");
		}
		else{
			printf("*****Details of the previous song*****\n");
			printf("Song Name: %s\n", prev_song->songName);
            printf("Singer: %s\n", prev_song->singer);
            printf("Lyricist: %s\n", prev_song->lyricist);
            printf("Film/Album: %s\n", prev_song->film);
            printf("Composer: %s\n", prev_song->composer);
            printf("Genre: %s\n", prev_song->genre);
            printf("Duration: %d seconds\n\n", prev_song->duration);
		}
	}
	else if(key==2)
	{
		   TreeNode* next_song=findNode(root,sNo+1);
  			if(!next_song){
    		printf("Next song details cannot be displayed\n");
		}
		else{
			printf("*****Details of the Next song*****\n");
			printf("Song Name: %s\n", next_song->songName);
            printf("Singer: %s\n", next_song->singer);
            printf("Lyricist: %s\n", next_song->lyricist);
            printf("Film/Album: %s\n", next_song->film);
            printf("Composer: %s\n", next_song->composer);
            printf("Genre: %s\n", next_song->genre);
            printf("Duration: %d seconds\n\n", next_song->duration);
		}
	}
	
    
}


//q7 Given a play-list and the serial number of the song, display details of the song. At this
//point, given an integer offset �k� and direction �up� or �down�, display the details of kth
//previous or kth next song, from the current song, respectively, in the play-list.
void DisplayplaylistDetails(TreeNode* playlist,int sNo){
	TreeNode* currSong= findNode(playlist,sNo);
	printf("***current playing song***\n");
	printf("Song Name: %s\n", currSong->songName);
    printf("Singer: %s\n", currSong->singer);
    printf("Lyricist: %s\n", currSong->lyricist);
    printf("Film/Album: %s\n", currSong->film);
    printf("Composer: %s\n", currSong->composer);
    printf("Genre: %s\n", currSong->genre);
    printf("Duration: %d seconds\n\n", currSong->duration);
    
    int k;
    printf("print details of an offset of k from the current song\nEnter the value of k\n");
    scanf("%d",&k);
    TreeNode* kprevSong=findNode(playlist,sNo-k);
    TreeNode* knextSong=findNode(playlist,sNo+k);
    
    int choice;
    printf("enter the choice to display kth previous song or kth next song.\nEnter 0 for kth prev song\nEnter 1 for kth next song\n");
    printf("enter the choice: ");
    scanf("%d",&choice);
    if(choice==0){
	    if(!kprevSong){
	    	printf("cannot display the details of the kth previous song");
		}
		else{
			
			 printf("***%dth song from current song***\n",k);
		     printf("Song Name: %s\n", kprevSong->songName);
	         printf("Singer: %s\n", kprevSong->singer);
	         printf("Lyricist: %s\n", kprevSong->lyricist);
	         printf("Film/Album: %s\n", kprevSong->film);
	         printf("Composer: %s\n", kprevSong->composer);
	         printf("Genre: %s\n", kprevSong->genre);
	         printf("Duration: %d seconds\n\n", kprevSong->duration);

		}
	
	}
	else if(choice==1){
	if(!knextSong){
    	printf("cannot display the details of kth next song");
	}
	else
	{
		
		 printf("***%dth song from current song***\n");
	     printf("Song Name: %s\n", knextSong->songName);
         printf("Singer: %s\n", knextSong->singer);
         printf("Lyricist: %s\n", knextSong->lyricist);
         printf("Film/Album: %s\n", knextSong->film);
         printf("Composer: %s\n", knextSong->composer);
         printf("Genre: %s\n", knextSong->genre);
         printf("Duration: %d seconds\n\n", knextSong->duration);

	}
	
}

	}

//q8 not working
TreeNode* createPlaylistfromCurrentSong(TreeNode* playlist,int s_no,TreeNode*root)
{
	TreeNode* currSong= findNode(playlist,s_no);
	PrintSongs(currSong);
	int numOfAtt, i;
    printf("Enter how many number of attributs of this song you want to select to create a new playlist based on their values\n");
    scanf("%d", &numOfAtt);
    char *attributes[numOfAtt];
    for(i=0; i<numOfAtt; i++){
        attributes[i] = (char*)malloc(50*sizeof(char));
        printf("Enter attribute %d ", i+1);
        scanf("%s", attributes[i]);
    }
    char* values[numOfAtt];
    int k=0;
    for(i=0;i<numOfAtt;i++){
        values[i] = (char*)malloc(50*sizeof(char));
    	if(strcmp(attributes[i], "singer") == 0)
		{
    		strcpy(values[i], currSong->singer);
		}
		else if(strcmp(attributes[i], "songName") == 0)
		{
			strcpy(values[i], currSong->songName);
		}
		
		else if(strcmp(attributes[i], "film") == 0)
		{
		    strcpy(values[i], currSong->film);
		}
		else if(strcmp(attributes[i], "composer") == 0)
		{
			strcpy(values[i], currSong->composer);
		}
		else if(strcmp(attributes[i], "genre") == 0)
		{
			strcpy(values[i], currSong->genre);
		}
		else if(strcmp(attributes[i], "lyricist") == 0){
			strcpy(values[i], currSong->lyricist);
		}
	}
	TreeNode* newPlaylist=CreatePlaylist(root, attributes,values,numOfAtt);
	for(int i=0; i<numOfAtt; i++){
		free(attributes[i]);
		free(values[i]);
	}
	return newPlaylist;
}
    



//q9
void filterPlayList(TreeNode* playlist, char* attribute_value){
	if(!playlist){
		return;
		
	}

		filterPlayList(playlist->left, attribute_value);

	if(strcmp(playlist->singer,attribute_value)==0 || strcmp(playlist->composer, attribute_value) == 0 || strcmp(playlist->film, attribute_value) == 0 || strcmp(playlist->genre, attribute_value) == 0 || strcmp(playlist->lyricist, attribute_value) == 0 || strcmp(playlist->songName, attribute_value) == 0) {
        printf("Song: %s\n", playlist->songName);
        printf("Singer: %s\n", playlist->singer);
        printf("Lyricist: %s\n", playlist->lyricist);
        printf("Film/Album: %s\n", playlist->film);
        printf("Composer: %s\n", playlist->composer);
        printf("Genre: %s\n", playlist->genre);
        printf("Duration: %d seconds\n\n", playlist->duration);
        printf("**************\n\n");
    }
		filterPlayList(playlist->right, attribute_value);

}


//q10
TreeNode* getSong(TreeNode *root, int offset){
	if(root == NULL){
		return NULL;
	}
	if(root->serialNumber == offset){
		return root;
	}
	if(offset < root->serialNumber){
		return getSong(root->left, offset);
	}
	return getSong(root->right, offset);
}

void shuffleToSomethingElse(TreeNode *root, char **attributes, char **values, int numOfAtt){
    int done = 0, i;
    int flag[dataBaseCount+1];
    for(i=1; i<=dataBaseCount; i++) flag[i] = 0;

    while(!done){
        TreeNode *reqSong;
        int songNum = abs(rand()) % dataBaseCount + 1;
        reqSong = getSong(root, songNum);
        if(!flag[songNum]){
            flag[songNum] = 1;
            int matches = countMatches(reqSong, numOfAtt, attributes, values);
            if(matches == numOfAtt){
                playSong(reqSong);
            }
        }
        int c = 0;
        for(i=1; i<=dataBaseCount; i++){
            if(flag[i] == 1){
                c++;
            }
        }
        if(c == dataBaseCount) done = 1;
    }
}


//q11
void performRangeSearch(TreeNode* root, char* singer1, char* singer2) {
    if (root == NULL) {
        return;
    }
    
    performRangeSearch(root->left, singer1, singer2);
    
    if (strcmp(root->singer, singer1) >= 0 && strcmp(root->singer, singer2) <= 0) {
        printf("singers: %s\n",root->singer);
    }
    
    performRangeSearch(root->right, singer1, singer2);
}



int main() 
{
    TreeNode* root = NULL;
    TreeNode* root1=NULL;
    int playListCount = -1;
    TreeNode* new_playlist[MAX_PLS];
    int choice;

    do {
        
        printf("\n*****MAIN MENU*****\n");
        printf("1. Insert Song\n");
        printf("2. Display Songs\n");
        printf("3. Print the songs from database in Ascending/descending order\n");
        printf("4. Delete the details as per song name and as per artist name\n");
        printf("5. Create a playlist\n");
        printf("6. Print playlist with serial number\n");
        printf("7. Print playlist with serial number and also print kth song above or below from current song\n");
        printf("8. Select one or many attributes of the current song and create a new playlist from the original database(creating a playlist is mandatory befor this!!)\n");
        printf("9. Filter the playlist according to given attribute's VALUE\n");
        printf("10. Shuffle to something else\n");
        printf("11. Perform Range Search using singer name\n");
        printf("12. Exit from the program\n");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice) 
		{
		
		    case 1:
                {
                  char filename[100];
                  printf("Enter the name of the input file: ");
                  scanf("%s", filename);
 
                  FILE* filePtr = fopen(filename, "r");
                  if (!filePtr)
                  {
                   printf("Unable to open file!\n");
                   break;
                  }

                  while (!feof(filePtr))
                  {
                  InsertSongFromFile(&root,filePtr); 
                  }

                  fclose(filePtr);
					insertSerialNumber(root);
                  printf("\nSongs Inserted Successfully!\n");
                  break;
                }
            case 2:
               PrintPlaylistinAscendingDescending(root);
               break;
               
            case 3:
			   PrintPlaylistinAscendingDescending(root);
			   break;   
               
            case 4:
				   char* song_name,*artist;
			   printf("enter the song name to be deleted\n");
			   scanf("%s",song_name);
			   printf("enter the name of the artist you want to delete");
			   scanf("%s",artist);
			   deleteNode(&root,song_name,artist);    
           
		    case 5:
                char* attributes[10];
                char* values[10];
                int num_attributes;
                printf("\nEnter the number of attributes to use for the playlist: ");
                scanf("%d", &num_attributes);
                for(int i=0; i<num_attributes; i++)
				{
                    attributes[i] = (char*)malloc(50*sizeof(char));
                    values[i] = (char*)malloc(50*sizeof(char));
                    printf("\nEnter attribute %d: ", i+1);
                    scanf("%s", attributes[i]);
                    printf("Enter value %d: ", i+1);
                    scanf("%s", values[i]);
                }
                new_playlist[++playListCount] = CreatePlaylist(root, attributes, values, num_attributes);
                printf("\nNew playlist created successfully!\n");
                printf("\nPlaylist:\n");
                insertSerialNumber(new_playlist[playListCount]);
                PrintInAscendingOrder(new_playlist[playListCount]);
               
               	for(int i=0; i<num_attributes; i++)
				{
                    free(attributes[i]);
                    free(values[i]);
                }
                break;           
		    case 6:
		    	insertSerialNumber(new_playlist[playListCount]);
                displayPlaylist(new_playlist[playListCount]);
                break;
                
            case 7:          
                int sNo;
                printf("enter the serial number of the playlist");
                scanf("%d",&sNo);
                DisplayplaylistDetails(new_playlist[playListCount],sNo);
            	break;
			        
            case 8:
            	{
            	    int s_no;
            	    printf("Enter the serial number\n");
            	    scanf("%d",&s_no);
            	    int pln;
            	    printf("Enter play list no(%d available) : ", playListCount+1);
            	    scanf("%d", &pln);
			        TreeNode* newplaylistroot=createPlaylistfromCurrentSong(new_playlist[pln-1],s_no,root);
			        PrintInAscendingOrder(newplaylistroot);			        
			        break;
			    
				} 
			
			case 9:
				char*attribute;
				char* attribute_value;
				attribute=(char*)malloc(sizeof(char)*10);
				attribute_value=(char*)malloc(sizeof(char)*10);
				printf("Enter a value to filter the play list like comedy,action..etc\n");
				scanf("%s",attribute_value);
				filterPlayList(new_playlist[playListCount],attribute_value);
				break;
			
			case 10:
				int numOfAtt;
          		printf("\nEnter the number of attributes to use for the playlist: ");
                scanf("%d", &numOfAtt);
                for(int i=0; i<numOfAtt; i++)
				{
                    attributes[i] = (char*)malloc(50*sizeof(char));
                    values[i] = (char*)malloc(50*sizeof(char));
                    printf("\nEnter attribute %d: ", i+1);
                    scanf("%s", attributes[i]);
                    printf("Enter value %d: ", i+1);
                    scanf("%s", values[i]);
                }
                shuffleToSomethingElse(root, attributes, values, numOfAtt);

                for(int i=0; i<numOfAtt; i++)
				{
                    free(attributes[i]);
                    free(values[i]);
                }
			    break;
				
			case 11:
				{
			    char singer1[50], singer2[50];
                printf("Enter the two singer names: ");
                scanf("%s %s", singer1, singer2);
                performRangeSearch(root, singer1, singer2);
                break;
				}					    		   
            case 12:
            	printf("Exiting....");
            	exit(0);
          
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice!=12);

    return 0;
}


