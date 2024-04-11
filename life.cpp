#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

// Класс для представления клетки
class Cell{  
  public:
    int pos_x;
    int pos_y;
    Cell(int x, int y){
      pos_x = x;
      pos_y = y;
    }
    void print_cell(){
      cout << pos_x << " ! " << pos_y << endl;
    }
};

// Класс для представления игрового поля
class Desk{
  private:
    int rows;
    int cols;
    int** life_matrix;
  public:
    
  // Конструктор для инициализации поля
  Desk(const int n = 3, const int m = 3, vector<Cell> st_gen = {}){
    rows = n;
    cols = m;
    
    life_matrix = new int*[n];
    for (int i = 0; i < n; i++){
      life_matrix[i] = new int[m];
    }
    for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
        life_matrix[i][j] = 0;
      }
    }
    for (auto i: st_gen){
      rule_cell(i.pos_x, i.pos_y);
    }
  }
  
  // Метод для вывода текущего состояния поля
  void print_population(){
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        cout << life_matrix[i][j] << " ";
      }
      cout << endl;
    }
    cout << std::flush;
  }
    
  // Метод для изменения состояния клетки
  void rule_cell(const int x, const int y){
    life_matrix[x][y] = !life_matrix[x][y];
  }
    
  void play();
  int status(const int x, const int y);
  vector<Cell> collect();
  
  ~Desk(){
  }
};

// Метод для определения статуса клетки на основе соседей
int Desk::status(const int x, const int y){
  int k = 0;
  for (int i = x-1; i <= x+1; i++){
    for (int j = y-1; j <= y+1; j++){
      if (i == x && j == y){
        continue;
      }
      k += life_matrix[i][j];
    }
  }
  if ((k == 3) && (life_matrix[x][y] == 0)){
    return 1;
  }
  if(((k < 2) || (k > 3)) && (life_matrix[x][y] == 1)){
    return 1;
  }
  return 0;
}

// Метод для сбора клеток, которые нужно изменить
vector<Cell> Desk::collect(){
  vector<Cell> ccv = {};
  for (int i = 1; i < rows-1; i++){
    for (int j = 1; j < cols-1; j++){
      if (status(i, j)){
        ccv.push_back(Cell(i, j));
      }
    }
  }
  return ccv;
}

// Метод для выполнения игры
void Desk::play(){
  
  vector<Cell> change_cell_v = {};
  change_cell_v = collect();
  for (auto i: change_cell_v){
    rule_cell(i.pos_x, i.pos_y);
  }
}

// Метод для разбора строки и создания вектора клеток
vector<Cell> parse_gen(string gen, const string delimiter){
  vector<Cell> a;
  auto it = a.end();
  size_t pos = 0;
  size_t pos_1 = 0;
  int x, y;
  string sp = " ";
  std::string token;
  
  while ((pos = gen.find(delimiter)) != std::string::npos) {
    token = gen.substr(0, pos);
    pos_1 = token.find(sp);
    string x_s = token.substr(0, pos_1);
    string y_s = token.substr(pos_1 + 1);
    x = stoi(x_s);
    y = stoi(y_s);
    a.push_back(Cell(x, y));
    gen.erase(0, pos + delimiter.length());
  }
  
  pos_1 = gen.find(sp);
  string x_s = gen.substr(0, pos_1);
  string y_s = gen.substr(pos_1 + 1);
  x = stoi(x_s);
  y = stoi(y_s);
  a.push_back(Cell(x, y));
    
  return a;
}

// Функция для вывода вектора клеток
void print_v(vector<Cell> gen){
  for (auto i: gen)
    i.print_cell();
}

int main(){
  
  string start_generation = "3 2, 3 3, 3 4, 2 4, 1 3"; // Начальное поколение
  
  vector<Cell> gen_v;
  
  gen_v = parse_gen(start_generation, ", ");
  
  Desk a(10, 10, gen_v); // Создание игрового поля
  
  for(;;){
    //sleep(1); // Пауза
    
    a.print_population(); // Вывод текущего состояния поля
    a.play(); // Выполнение хода
    cout << "-----------------\n"<< std::flush;
    //sleep(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    system("clear");
  }
  
  return 0;
}
