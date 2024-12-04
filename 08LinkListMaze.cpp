#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
    Grid(int s = 0) // 使用成員初始化列表
    {
        state = s;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
    }
    Grid *getDir(int d) { return dir[d]; }
    int getState() { return state; }
    void setDir(int d, Grid *g) { dir[d] = g; }
    void setState(int s) { state = s; }
private:
    Grid *dir[4]; // 上、下、左、右指標
    int state;    // 狀態 0: 空地, 1: 牆壁
};

struct List
{
public:
    List()
    {
        top = 0;
    }
    void addElement(Grid *g)
    {
        if (top < SIZE * SIZE) // 確保不超出範圍
        {
            data[top++] = g;
        }
    }
    
    Grid *removeElement()
    {
        if (top > 0)
        {
            return data[--top];
        }
        return NULL;
    }
    
    void printPath()
    {
        int j;
        for(j = 1; j < top; j++)
        {
            if(data[j] == data[j - 1]->getDir(UP))
            {
                cout<<"UP\n";
            }
            else if(data[j] == data[j - 1]->getDir(DOWN))
            {
                cout<<"DOWN\n";
            }
            else if(data[j] == data[j - 1]->getDir(LEFT))
            {
                cout<<"LEFT\n";
            }
            else if(data[j] == data[j - 1]->getDir(RIGHT))
            {
                cout<<"RIGHT\n";
            }
        }
    }
private:
    Grid *data[SIZE * SIZE];
    int top;
};

class Maze
{
public:
    Maze()
    {
        initMaze(SIZE); // 初始化迷宮
    }
    
    void initMaze(int s)
    {
        srand(time(0)); // 初始化隨機數生成器
        maze = new Grid(0); // 初始化左上角
        Grid *prev_row = maze, *curr_row = maze, *prev_grid = maze, *curr_grid;
        
        int wall = s * s * 0.2; // 計算牆壁數量（20%）

        // 創建迷宮格子並連接上下左右指標
        for (int i = 0; i < s; ++i)
        {
            if (i > 0) // 建立新的一行
            {
                curr_row = new Grid(0);
                prev_row->setDir(DOWN, curr_row);
                curr_row->setDir(UP, prev_row);
                prev_row = curr_row;
            }

            for (int j = 1; j < s; ++j)
            {
                curr_grid = new Grid(0); // 預設為空地

                // 向右連接
                curr_row->setDir(RIGHT, curr_grid);
                curr_grid->setDir(LEFT, curr_row);

                if (i > 0) // 向上連接
                {
                    prev_grid->setDir(DOWN, curr_grid);
                    curr_grid->setDir(UP, prev_grid);
                }

                curr_row = curr_grid;
                if (prev_grid != NULL) prev_grid = prev_grid->getDir(RIGHT);
            }

            prev_grid = prev_row->getDir(RIGHT); // 移動到下一行的開頭
        }

        // 隨機分配牆壁，直到達到 wallCount
        while (wall)
        {
            int i = rand() % s;
            int j = rand() % s;
            Grid* target = findGrid(maze, i, j);

            if (target != NULL && target->getState() != 1 && !(i == 0 && j == 0) && !(i == s-1 && j == s-1))
            {
                target->setState(1);
                wall--;
            }
        }
    }
    
    List *getPath()
    {
        List *path = new List();
        findPath(maze, path);
        return path;
    }
    
    void printMaze()
    {
        Grid *j = maze, *k;
        while(j != NULL)
        {
            k = j;
            while(k != NULL)
            {
                cout<<k->getState();
                k = k->getDir(RIGHT); 
            }
            cout<<endl;
            j = j->getDir(DOWN);
        }
    }
    
private:
    Grid *maze;

    bool findPath(Grid *current, List *path)
    {
        if (current == NULL || current->getState() == 1) // 如果當前格子是牆壁或空
        {
            return false;
        }
        
        path->addElement(current); // 將當前的格子加入路徑
        current->setState(1);      // 標記為已訪問

        // 終點條件：當前格子沒有右邊和下邊，代表到達終點
        if (current->getDir(DOWN) == NULL && current->getDir(RIGHT) == NULL)
        {
            return true;
        }

        // 試圖向四個方向遞迴尋找路徑
        if (findPath(current->getDir(UP), path))
        {
            return true;
        }
        if (findPath(current->getDir(DOWN), path))
        {
            return true;
        }
        if (findPath(current->getDir(LEFT), path))
        {
            return true;
        }
        if (findPath(current->getDir(RIGHT), path))
        {
            return true;
        }

        // 若找不到路徑則回溯
        path->removeElement();
        return false;
    }

    // 尋找特定行列的格子
    Grid* findGrid(Grid* start, int targetRow, int targetCol)
    {
        Grid* rowPointer = start;
        int currentRow = 0;

        // 移動到目標行
        while (rowPointer != NULL && currentRow < targetRow)
        {
            rowPointer = rowPointer->getDir(DOWN);
            currentRow++;
        }

        // 移動到目標列
        if (rowPointer != NULL && currentRow == targetRow)
        {
            Grid* colPointer = rowPointer;
            int currentCol = 0;

            while (colPointer != NULL && currentCol < targetCol)
            {
                colPointer = colPointer->getDir(RIGHT);
                currentCol++;
            }

            if (currentCol == targetCol)
            {
                return colPointer;
            }
        }

        return NULL;
    }
};

int main()
{
    Maze *maze = new Maze();
    maze->printMaze();
    maze->getPath()->printPath();
}
