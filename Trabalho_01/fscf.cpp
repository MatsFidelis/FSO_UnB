#include <iostream>
#include <queue>

using namespace std;

class Processo
{
protected:
    int id;
    int tempoRestante;
    int prioridade;

public:
    Processo()
    {
        prioridade = -1;
    }
    void setProcesso(int id_)
    {
        id = id_;
        tempoRestante = id * 10;
    };
    int getTempoRestante()
    {
        return tempoRestante;
    }
    int getId()
    {
        return id;
    }
    void executaProcesso()
    {
        tempoRestante -= 10;
    }
    void setPrioridade(int x)
    {
        prioridade = x;
    }
    int getPrioridade()
    {
        return prioridade;
    }
};

int main()
{
    int tempoTotal = 0;

    int qntProcessos, idProcesso, pAcao;

    queue<Processo> fila;

    cin >> qntProcessos;

    Processo processoArray[200];

    for (int i = 0; i < qntProcessos; i++)
    {
        cin >> idProcesso;

        processoArray[i].setProcesso(idProcesso);

        fila.push(processoArray[i]);
    }

    while (!fila.empty())
    {
        Processo Patual = fila.front();

        if (fila.front().getPrioridade() == 1)
        {
            fila.front().executaProcesso();
            tempoTotal += 10;
            fila.front().setPrioridade(-1);

            if (fila.front().getTempoRestante() == 0)
            {
                cout << Patual.getId() << " (" << tempoTotal << ")" << endl;
                fila.pop();
            }
            
        } else {

        cin >> pAcao;

        if (pAcao == 1)
        {
            fila.pop();
            Patual.setPrioridade(1);
            fila.push(Patual);
        } else if(pAcao == 0) {
            fila.front().executaProcesso();
            tempoTotal += 10;
            if (fila.front().getTempoRestante() == 0)
            {
                cout << Patual.getId() << " (" << tempoTotal << ")" << endl;
                fila.pop();
            }
        }

        }
    }

    return 0;
}