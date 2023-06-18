#include <iostream>
#include <random>
#include "GraphList.cpp"
#include "GraphMatrix.cpp"
using namespace std;

int main(){

    while(true){
        int decision;
        int blank;
        GraphList* graphList = new GraphList(true, 5, 0.66, false);
        GraphMatrix* graphMatrix = new GraphMatrix(true, 5, 0.66, false);

        system ("CLS");
        cout << "Wybierz reprezentacje:" << endl;
        cout << "1. Lista" << endl;
        cout << "2. Macierz" << endl;
        cin >> decision;
        bool isChosen = true;
        while(isChosen){
            switch(decision){
                case 1:
                    int what;
                    system ("CLS");
                    cout << "1. Wczytaj dane z pliku (graf nieskierowany)" << endl;
                    cout << "2. Wczytaj dane z pliku (graf skierowany)" << endl;
                    cout << "3. Wygeneruj graf losowo (graf nieskierowany)" << endl;
                    cout << "4. Wygeneruj graf losowo (graf skierowany)" << endl;
                    cout << "5. Wyswietl graf" << endl;
                    cout << "6. Algorytm Prima" << endl;
                    cout << "7. Algorytm Kruskala" << endl;
                    cout << "8. Algorytm Dijstry" << endl;
                    cout << "9. Algorytm Bellmana-Forda" << endl;
                    cout << "10. Wroc" << endl;
                    cin >> what;
                    int ver;
                    double den;
                    switch(what){
                        case 1:{
                            graphList = new GraphList(true, 0, 0, false);
                        }
                            break;
                        case 2:{
                            graphList = new GraphList(true, 0, 0, true);
                        }
                            break;
                        case 3:{
                            cout << "Liczba wierzcholkow: ";
                            cin >> ver;
                            cout << "\nGestosc: ";
                            cin >> den;
                            graphList = new GraphList(false, ver, den, false);
                        }
                            break;
                        case 4:{
                            cout << "Liczba wierzcholkow: ";
                            cin >> ver;
                            cout << "\nGestosc: ";
                            cin >> den;
                            graphList = new GraphList(false, ver, den, true);
                        }
                            break;
                        case 5:
                            system ("CLS");
                            graphList->printList();
                            cin >> blank;
                            break;
                        case 6:{
                                system ("CLS");
                                int* final = graphList -> algPrim();
                                int minWeight = 0;
                                for(int i = 0; i < graphList -> V; i++){
                                    if(final[i] != -1) cout << i << ":" << final[i] << " Waga:" << graphList -> array[i].search(final[i]) -> weight << ",  " << endl;
                                    if(final[i] != -1) minWeight += graphList -> array[i].search(final[i]) -> weight;
                                }
                                cout << "Calkowita waga drzewa: " << minWeight;
                                cin >> blank;
                            }
                            break;
                        case 7:{
                                system ("CLS");
                                int** final = graphList -> algKruskal();
                                int minWeight = 0;
                                for(int i = 0; i < graphList -> V - 1; i++){
                                    cout << final[i][0] << "-" << final[i][1] << ": "<< graphList->array[final[i][0]].search(final[i][1])->weight << "\n";
                                     minWeight += graphList->array[final[i][0]].search(final[i][1])->weight;
                                 }
                                cout << "Koszt: " << minWeight;
                                cin >> blank;
                            }
                            break;
                        case 8:{
                            system ("CLS");
                            int start;
                            int end;
                            cout << "Poczatek: ";
                            cin >> start;
                            cout << "\nKoniec: ";
                            cin >> end;
                            auto solution = graphList -> algDijstra(start);
                            cout << "Dlugosc sciezki: ";
                            cout << solution[end].key << endl;
                            cout << "Sciezka: ";
                            int i = 0;
                            int endnode = end;
                            while(endnode != -1){
                                cout << solution[endnode].vertex << " <- ";
                                if(endnode == start) endnode = -1;
                                else endnode = solution[endnode].before->vertex;
                                i++;
                            }
                            cin >> blank;
                        }
                            break;
                        case 9:{
                            system ("CLS");
                            int start;
                            int end;
                            cout << "Poczatek: ";
                            cin >> start;
                            cout << "\nKoniec: ";
                            cin >> end;
                            auto solution = graphList -> algBelFord(start);
                            cout << "Dlugosc sciezki: ";
                            cout << solution[end].key << endl;
                            cout << "Sciezka: ";
                            int i = 0;
                            int endnode = end;
                            while(endnode != -1){
                                cout << solution[endnode].vertex << " <- ";
                                if(endnode == start) endnode = -1;
                                else endnode = solution[endnode].before->vertex;
                                i++;
                            }
                            cin >> blank;
                        }
                        break;
                        case 10:
                            isChosen = false;
                            break;

                    }
                    break;
                case 2: {
                    int who;
                    cout << "fjnie";
                    system("CLS");
                    cout << "fjnie";
                    cout << "1. Wczytaj dane z pliku (graf nieskierowany)" << endl;
                    cout << "2. Wczytaj dane z pliku (graf skierowany)" << endl;
                    cout << "3. Wygeneruj graf losowo (graf nieskierowany)" << endl;
                    cout << "4. Wygeneruj graf losowo (graf skierowany)" << endl;
                    cout << "5. Wyswietl graf" << endl;
                    cout << "6. Algorytm Prima" << endl;
                    cout << "7. Algorytm Kruskala" << endl;
                    cout << "8. Algorytm Dijstry" << endl;
                    cout << "9. Algorytm Bellmana-Forda" << endl;
                    cout << "10. Wroc" << endl;
                    cin >> who;
                    int ver;
                    double den;
                    switch (who) {
                        case 1: {
                            graphMatrix = new GraphMatrix(true, 0, 0, false);
                        }
                            break;
                        case 2: {
                            graphMatrix = new GraphMatrix(true, 0, 0, true);
                        }
                            break;
                        case 3: {
                            cout << "Liczba wierzcholkow: ";
                            cin >> ver;
                            cout << "\nGestosc: ";
                            cin >> den;
                            graphMatrix = new GraphMatrix(false, ver, den, false);
                        }
                            break;
                        case 4: {
                            cout << "Liczba wierzcholkow: ";
                            cin >> ver;
                            cout << "\nGestosc: ";
                            cin >> den;
                            graphMatrix = new GraphMatrix(false, ver, den, true);
                        }
                            break;
                        case 5:
                            system("CLS");
                            graphMatrix->printMatrix();
                            cin >> blank;
                            break;
                        case 6: {
                            system("CLS");
                            int *final = graphMatrix->algPrim();
                            int minWeight = 0;
                            for (int i = 0; i < graphMatrix->E; i++) {
                                for (int j = 1; j < graphMatrix->V; j++) {
                                    if (graphMatrix->matrix[j][i].edge == graphMatrix->matrix[final[j]][i].edge &&
                                        graphMatrix->matrix[j][i].weight != 0) {
                                        cout << j << ":" << final[j] << " Waga:" << graphMatrix->matrix[j][i].weight
                                             << ",  " << endl;
                                        minWeight += graphMatrix->matrix[j][i].weight;
                                    }
                                }
                            }
                            cout << "Calkowita waga drzewa: " << minWeight;
                            cin >> blank;
                        }
                            break;
                        case 7: {
                            int **final = graphMatrix->algKruskal();
                            int minWeight = 0;
                            for (int i = 0; i < graphMatrix->V - 1; i++) {
                                bool found = false;
                                int j = 0;
                                while (!found) {
                                    if (graphMatrix->matrix[final[i][0]][j].edge != 0 &&
                                        graphMatrix->matrix[final[i][1]][j].edge != 0) {
                                        cout << final[i][0] << "-" << final[i][1] << ": "
                                             << graphMatrix->matrix[final[i][0]][j].weight << endl;
                                        minWeight += graphMatrix->matrix[final[i][0]][j].weight;
                                        found = true;
                                    }
                                    j++;
                                }
                            }
                            cout << "Koszt: " << minWeight;
                            cin >> blank;
                        }
                            break;
                        case 8: {
                            system("CLS");
                            int start;
                            int end;
                            cout << "Poczatek: ";
                            cin >> start;
                            cout << "\nKoniec: ";
                            cin >> end;
                            auto solution = graphMatrix->algDijstra(start);
                            cout << "Dlugosc sciezki: ";
                            cout << solution[end].key << endl;
                            cout << "Sciezka: ";
                            int i = 0;
                            int endnode = end;
                            while (endnode != -1) {
                                cout << solution[endnode].vertex << " <- ";
                                if (endnode == start) endnode = -1;
                                else endnode = solution[endnode].before->vertex;
                                i++;
                            }
                            cin >> blank;
                        }
                            break;
                        case 9: {
                            system("CLS");
                            int start;
                            int end;
                            cout << "Poczatek: ";
                            cin >> start;
                            cout << "\nKoniec: ";
                            cin >> end;
                            auto solution = graphMatrix->algBelFord(start);
                            cout << "Dlugosc sciezki: ";
                            cout << solution[end].key << endl;
                            cout << "Sciezka: ";
                            int i = 0;
                            int endnode = end;
                            while (endnode != -1) {
                                cout << solution[endnode].vertex << " <- ";
                                if (endnode == start) endnode = -1;
                                else endnode = solution[endnode].before->vertex;
                                i++;
                            }
                            cin >> blank;
                        }
                            break;
                        case 10:
                            isChosen = false;
                            break;
                    }
                }
                    break;
            }
        }
    }
   return 0;
}