#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);
void search(const int Size, char puzzle[][Size], const int wordSize,
            char* word);
bool inBounds(int row, int col, const int Size);
bool check1D(const int Size, char puzzle[][Size], const int wordSize,
             char* word, int rowLoc, int colLoc, int dir);

int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);
  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");
  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }
  free(word);
  return 0;
}

void search(const int Size, char puzzle[][Size], const int wordSize,
            char* word) {
  for (int row = 1; row < Size + 1; row++) {
    for (int col = 1; col < Size + 1; col++) {
      for (int i = 0; i < 7; i++) {
        if (check1D(Size, puzzle, wordSize, word, row - 1, col - 1, i)) {
          printf(word);
          if (i == 0) {
            printf(
                " can be found at row , col = (%d, %d) in the north-west "
                "direction.\n",
                row, col);
          } else if (i == 1) {
            printf(
                " can be found at row , col = (%d, %d) in the north "
                "direction.\n",
                row, col);
          } else if (i == 2) {
            printf(
                " can be found at row , col = (%d, %d) in the west "
                "direction.\n",
                row, col);
          } else if (i == 3) {
            printf(
                " can be found at row , col = (%d, %d) in the southwest "
                "direction.\n",
                row, col);
          } else if (i == 4) {
            printf(
                " can be found at row , col = (%d, %d) in the north-east "
                "direction.\n",
                row, col);
          } else if (i == 5) {
            printf(
                " can be found at row , col = (%d, %d) in the east "
                "direction.\n",
                row, col);
          } else if (i == 6) {
            printf(
                " can be found at row , col = (%d, %d) in the south "
                "direction.\n",
                row, col);
          } else if (i == 7) {
            printf(
                " can be found at row , col = (%d, %d) in the south-east "
                "direction.\n",
                row, col);
          }
          return;
        }
      }
    }
  }
  printf(word);
  printf(" cannot be found!");
  return;
}

char* readWord(int* wordSize) {
  printf("How many characters are there in the word?\n");
  scanf("%d", wordSize);
  char* word = (char*)malloc(*wordSize * sizeof(char));
  printf("What is the word that you are looking for?\n");
  for (int i = 0; i < *wordSize; i++) {
    scanf(" %c", &word[i]);
  }

  return word;
}

void readWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("Please enter the word puzzle:\n");
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      scanf(" %c", &puzzle[row][col]);
    }
  }
  return;
}

bool inBounds(int row, int col, const int Size) {
  return col >= 0 && col < Size && row >= 0 && row < Size;
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("The word puzzle entered is\n");
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      printf("%c ", puzzle[row][col]);
    }
    printf("\n");
  }
  return;
}

void printWord(char* word, const int wordSize) {
  for (int i = 0; i < wordSize; i++) {
    printf("%c", word[i]);
  }
}

bool check1D(const int Size, char puzzle[][Size], const int wordSize,
             char* word, int rowLoc, int colLoc, int dir) {
  if (dir == 0) {
    // northwest
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc - i, colLoc - i, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc - i][colLoc - i])) {
        return false;
      }
    }
    return true;
  } else if (dir == 1) {
    // north
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc - i, colLoc, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc - i][colLoc])) {
        return false;
      }
    }
    return true;
  } else if (dir == 2) {
    // west
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc, colLoc - i, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc][colLoc - i])) {
        return false;
      }
    }
    return true;
  } else if (dir == 3) {
    // southwest
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc + i, colLoc - i, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc + i][colLoc - i])) {
        return false;
      }
    }
    return true;
  } else if (dir == 4) {
    // northeast
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc - i, colLoc + i, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc - i][colLoc + i])) {
        return false;
      }
    }
    return true;
  } else if (dir == 5) {
    // east
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc, colLoc + i, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc][colLoc + i])) {
        return false;
      }
    }
    return true;
  } else if (dir == 6) {
    // south
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc + i, colLoc, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc + i][colLoc])) {
        return false;
      }
    }
    return true;
  } else if (dir == 7) {
    // southeast
    for (int i = 0; i < wordSize; i++) {
      if (!inBounds(rowLoc + i, colLoc + i, Size)) {
        return false;
      }
      if (!(word[i] == puzzle[rowLoc + i][colLoc + i])) {
        return false;
      }
    }
  }
  return true;
}