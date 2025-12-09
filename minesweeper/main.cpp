#include <iostream>
#include <ctime>
using namespace std;

const int SIZE = 5;
const int MINES = 5;

char field[SIZE][SIZE];
bool mines[SIZE][SIZE];
bool generated = false;

void init() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = '#';
            mines[i][j] = false;
        }
}

void generateMines(int fx, int fy) {
    srand(time(0));
    int placed = 0;

    while (placed < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if ((x == fx && y == fy) || mines[x][y])
            continue;

        mines[x][y] = true;
        placed++;
    }

    generated = true;
}

int countMines(int x, int y) {
    int count = 0;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;

            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE)
                if (mines[nx][ny])
                    count++;
        }

    return count;
}

void openCell(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
        return;

    if (field[x][y] != '#')
        return;

    int m = countMines(x, y);
    field[x][y] = m + '0';

    if (m == 0) {
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (i != 0 || j != 0)
                    openCell(x + i, y + j);
    }
}

void printField() {
    cout << "  ";
    for (int i = 0; i < SIZE; i++)
        cout << i << " ";
    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++)
            cout << field[i][j] << " ";
        cout << endl;
    }
}

int main() {
    init();
    int safeCells = SIZE * SIZE - MINES;
    int opened = 0;

    while (true) {
        printField();

        int x, y;
        cout << "\nEnter coordinates (x y): ";
        cin >> x >> y;

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Invalid coordinates!\n";
            continue;
        }

        if (!generated)
            generateMines(x, y);

        if (mines[x][y]) {
            cout << "\nGame over!\n";
            break;
        }

        if (field[x][y] != '#') {
            cout << "Cell already opened!\n";
            continue;
        }

        int before = opened;

        openCell(x, y);

        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (field[i][j] != '#' && field[i][j] != '*')
                    opened++;

        if (opened == safeCells) {
            cout << "\nYou win!\n";
            break;
        }

        opened = 0;
    }

    cout << "\nFinal field:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (mines[i][j])
                cout << "* ";
            else
                cout << countMines(i, j) << " ";
        }
        cout << endl;
    }

    return 0;
}
