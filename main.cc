#include <iostream>
#include <iomanip>
using namespace std;

// Função para iniciar o dia, configurando os valores iniciais do caminhão
void iniciarDia(float &pesoMaximo, int &volumeMaximo, float *&pesos, float *&valores, float *&transporte, float *&seguro)
{
    cout << "\nIniciando dia..." << endl;

    do
    {
        cout << "\nInforme o Volume Máximo do caminhão em m³ (entre 5 e 15m³): ";
        cin >> volumeMaximo;

    } while (volumeMaximo < 5 || volumeMaximo > 15);

    do
    {
        cout << "\nInforme o Peso Máximo em kg, o valor deve ser maior que 0: ";
        cin >> pesoMaximo;

    } while (pesoMaximo <= 0);

    // Realocação dos arrays com o tamanho adequado
    pesos = new float[volumeMaximo];
    valores = new float[volumeMaximo];
    transporte = new float[volumeMaximo];
    seguro = new float[volumeMaximo];

    cout << fixed << setprecision(2);
    cout << "\nAs capacidades máximas do caminhão foram definidas. Peso Máximo: " << pesoMaximo << "kg - Volume Máximo: " << volumeMaximo << "m³." << endl;
}

// Função para inserir um pacote no caminhão
void inserirPacote(float *&pesos, float *&valores, int &volumeAtual, float pesoMaximo, int volumeMaximo, float *&transporte, float *&seguro, float &pesoAtual)
{
    if (volumeAtual >= volumeMaximo)
    {
        cout << "\nO caminhão já se encontra cheio, não é possível adicionar mais pacotes." << endl;
        return;
    }

    float pesoPacote;
    float valorMercadoria;

    do
    {
        cout << "\nInforme o peso do pacote (entre 1kg e 99kg): ";
        cin >> pesoPacote;
    } while (pesoPacote < 1 || pesoPacote > 99);

    if (pesoAtual + pesoPacote > pesoMaximo)
    {
        cout << "\nO peso total ultrapassaria o peso máximo permitido. Pacote não adicionado." << endl;
        return;
    }

    do
    {
        cout << "\nInforme o valor da mercadoria: ";
        cin >> valorMercadoria;
    } while (valorMercadoria < 0);

    float custoTransporte = pesoPacote * 3.50;
    float taxaSeguro = valorMercadoria * 0.05;
    float custoTotal = custoTransporte + taxaSeguro;

    cout << fixed << setprecision(2);
    cout << "\nPeso do pacote: " << pesoPacote << "kg" << endl;
    cout << "Valor da mercadoria: R$" << valorMercadoria << endl;
    cout << "Custo do Transporte: R$" << custoTransporte << endl;
    cout << "Taxa do Seguro: R$" << taxaSeguro << endl;
    cout << "Custo Total das Taxas(Transporte + Seguro): R$" << custoTotal << endl;

    char resposta;
    do
    {
        cout << "\nVocê deseja continuar com os valores informados (S/N)? ";
        cin >> resposta;

        if (resposta == 'S' || resposta == 's')
        {
            pesos[volumeAtual] = pesoPacote;
            valores[volumeAtual] = valorMercadoria;
            transporte[volumeAtual] = custoTransporte;
            seguro[volumeAtual] = taxaSeguro;
            volumeAtual++;
            pesoAtual += pesoPacote;
            cout << "\nPacote inserido com sucesso no caminhão." << endl;
            break;
        }
        else if (resposta == 'N' || resposta == 'n')
        {
            cout << "\nOperação Cancelada." << endl;
            break;
        }
        else
        {
            cout << "\nOpção Inválida, tente novamente." << endl;
        }
    } while (resposta != 'S' || resposta != 's' || resposta != 'N' || resposta != 'n');
}

// Função para retirar um pacote do caminhão
void retirarPacote(float *&pesos, float *&valores, float *&transporte, float *&seguro, int &volumeAtual, float &pesoAtual)
{
    int posicao;
    char resposta;

    cout << "\nInforme a posição do pacote: ";
    cin >> posicao;

    if (posicao < 0 || posicao >= volumeAtual)
    {
        cout << "\nPacote não encontrado na posição informada." << endl;
        return;
    }

    cout << "\nPacote encontrado na posição " << posicao << " com peso " << pesos[posicao] << "kg." << endl;

    do
    {
        cout << "\nVocê deseja continuar com os valores informados (S/N)? ";
        cin >> resposta;

        if (resposta == 'S' || resposta == 's')
        {
            pesoAtual -= pesos[posicao]; // Removendo o peso do pacote removido
            cout << "\nPacote retirado com sucesso." << endl;

            // Movendo os dados do final para a posição do pacote retirado
            for (int i = posicao; i < volumeAtual - 1; i++)
            {
                pesos[i] = pesos[i + 1];
                valores[i] = valores[i + 1];
                transporte[i] = transporte[i + 1];
                seguro[i] = seguro[i + 1];
            }

            volumeAtual--;
            break;
        }
        else if (resposta == 'N' || resposta == 'n')
        {
            cout << "\nOperação Cancelada." << endl;
            break;
        }
        else
        {
            cout << "\nOpção Inválida, tente novamente." << endl;
        }
    } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');
}

// Função para consultar a situação atual do caminhão
void consultarSituacao(float *&pesos, float pesoMaximo, int &volumeAtual, int volumeMaximo, float *&transporte, float *&seguro, float *&valores, float pesoAtual)
{
    float pesoRestante = pesoMaximo - pesoAtual;
    int qtdRestante = volumeMaximo - volumeAtual;

    float totalTransporte = 0;
    float totalSeguro = 0;
    float totalValor = 0;

    for (int i = 0; i < volumeAtual; i++)
    {
        totalTransporte += transporte[i];
        totalSeguro += seguro[i];
        totalValor += valores[i];
    }

    cout << fixed << setprecision(2);
    cout << "\nPeso carregado no momento: " << pesoAtual << "kg." << endl;
    cout << "Peso Restante: " << pesoRestante << "kg." << endl;
    cout << "Quantidade de pacotes carregados: " << volumeAtual << endl;
    cout << "Quantidade de pacotes restantes: " << qtdRestante << endl;
    cout << "Valor total de mercadoria: R$" << totalValor << endl;
    cout << "Valor total de transporte: R$" << totalTransporte << endl;
    cout << "Valor total de seguro: R$" << totalSeguro << endl;
}

// Função para listar os pacotes no caminhão
void listarPacotes(float *&pesos, int volumeAtual, int volumeMaximo)
{
    cout << "\nListagem dos pacotes no caminhão:" << endl;

    // Imprime a linha superior da carroceria do caminhão
    cout << " ______" << endl;
    cout << "/__|   |" << endl;

    // Imprime os pesos dos pacotes ao longo da linha
    cout << "-------";
    for (int i = 0; i < volumeMaximo; i++)
    {
        if (i < volumeAtual)
        {
            cout << fixed << setprecision(2);
            cout << "|" << pesos[i];
        }
        else
        {
            // Se não houver pacote carregado nessa posição, imprime um espaço em branco
            cout << "|  ";
        }
    }

    // Imprime a linha inferior da carroceria do caminhão
    cout << "|" << endl;
    cout << "\\-()---|/()()\\";

    // Para imprimir as rodas de baixo verifica o tamanhão do caminhão, se for menor ou igual a 6 ele utiliza um espaçamento menor, e se for maior que 6 posiciona as rodas mais próximo ao final do caminhão
    int espacos = (volumeMaximo - 2) * 2;
    cout << string(espacos, ' ') << "/()()\\" << endl;
}

// Função para finalizar o dia de trabalho
void finalizarDia(float *&pesos, float *&valores, float *&transporte, float *&seguro, int volumeAtual)
{
    if (volumeAtual == 0)
    {
        cout << "\nNão existe pacotes sendo transportados para gerar o relatório de finalizar dia." << endl;
        return;
    }

    float pesoMaisLeve = pesos[0];
    float pesoMaisPesado = pesos[0];
    int posicaoPesoMaisLeve = 0;   // Inicializado com a primeira posição
    int posicaoPesoMaisPesado = 0; // Inicializado com a primeira posição
    float custoMaisAlto = transporte[0] + seguro[0];
    int posicaoCustoMaisAlto = 0; // Inicializado com a primeira posição
    float totalFrete = 0;
    float totalSeguro = 0;
    float totalPesoDia = 0;

    for (int i = 0; i < volumeAtual; i++)
    {
        // Pacote mais leve
        if (pesos[i] < pesoMaisLeve)
        {
            pesoMaisLeve = pesos[i];
            posicaoPesoMaisLeve = i;
        }

        // Pacote mais pesado
        if (pesos[i] > pesoMaisPesado)
        {
            pesoMaisPesado = pesos[i];
            posicaoPesoMaisPesado = i;
        }

        // Custo mais alto
        float custoTotal = transporte[i] + seguro[i];
        if (custoTotal > custoMaisAlto)
        {
            custoMaisAlto = custoTotal;
            posicaoCustoMaisAlto = i;
        }

        // Total Frete
        totalFrete += transporte[i];

        // Total Seguro
        totalSeguro += seguro[i];

        // Total Peso do Dia
        totalPesoDia += pesos[i];
    }

    // Imprime o relatório do dia de trabalho
    cout << fixed << setprecision(2);
    cout << "\n...: Relatório do dia :..." << endl;
    cout << "Peso do pacote transportado mais leve: " << pesoMaisLeve << "kg - Posição: " << posicaoPesoMaisLeve << endl;
    cout << "Peso do pacote transportado mais pesado: " << pesoMaisPesado << "kg - Posição: " << posicaoPesoMaisPesado << endl;
    cout << "Pacote transportado com maior custo total (frete + seguro): " << custoMaisAlto << "kg - Posição: " << posicaoCustoMaisAlto << endl;
    cout << "Valor total do frete durante todo o dia: R$" << totalFrete << endl;
    cout << "Valor total do seguro durante todo o dia: R$" << totalSeguro << endl;
    cout << "Peso total transportado durante todo o dia: " << totalPesoDia << "kg" << endl;
}

int main()
{
    int opcao;

    float pesoMaximo = 0; // em kg
    int volumeMaximo = 0; // em m³ (entre 5 e 15)

    // Arrays criados com valor nulo, para ser atribuido o tamanho correto ao iniciar o dia
    float *pesos = nullptr;      // Ponteiro para a lista de pesos dos itens
    float *valores = nullptr;    // Ponteiro para a lista de valores dos itens respectivos
    float *transporte = nullptr; // Ponteiro com os valores de frete
    float *seguro = nullptr;     // Ponteiro com os valores de seguro

    int volumeAtual = 0; // Volume atual no caminhão
    float pesoAtual = 0; // Peso atual no caminhão

    do
    {
        cout << "\n...: MENU :..." << endl;
        cout << "1. Iniciar dia" << endl;
        cout << "2. Inserir pacote" << endl;
        cout << "3. Retirar pacote" << endl;
        cout << "4. Consultar situação" << endl;
        cout << "5. Listar pacotes" << endl;
        cout << "6. Finalizar dia" << endl;
        cout << "7. Sair" << endl;

        cout << "\nEscolha uma opção: " << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            // Verifica se o dia já foi iniciado anteriormente
            if (volumeMaximo != 0 || pesoMaximo != 0)
            {
                cout << "\nVocê já iniciou o dia com outros valores para o caminhão, se deseja iniciar com valores diferentes, finalize o dia primeiro." << endl;
                break;
            }
            else
            {
                iniciarDia(pesoMaximo, volumeMaximo, pesos, valores, transporte, seguro);
                break;
            }

        case 2:
            if (pesoMaximo != 0 && volumeMaximo != 0)
            {
                inserirPacote(pesos, valores, volumeAtual, pesoMaximo, volumeMaximo, transporte, seguro, pesoAtual);
            }
            else
            {
                cout << "\nVocê deve iniciar o dia para conseguir adicionar e remover pacotes." << endl;
            }
            break;

        case 3:
            if (pesoMaximo != 0 && volumeMaximo != 0)
            {
                retirarPacote(pesos, valores, transporte, seguro, volumeAtual, pesoAtual);
            }
            else
            {
                cout << "\nVocê deve iniciar o dia para conseguir adicionar e remover pacotes." << endl;
            }
            break;

        case 4:
            if (pesoMaximo != 0 && volumeMaximo != 0)
            {
                consultarSituacao(pesos, pesoMaximo, volumeAtual, volumeMaximo, transporte, seguro, valores, pesoAtual);
            }
            else
            {
                cout << "\nVocê deve iniciar o dia para conseguir consultar a situação do transporte." << endl;
            }
            break;

        case 5:
            if (pesoMaximo != 0 && volumeMaximo != 0)
            {
                listarPacotes(pesos, volumeAtual, volumeMaximo);
            }
            else
            {
                cout << "\nVocê deve iniciar o dia para conseguir listar os pacotes transportados." << endl;
            }
            break;

        case 6:
            char resposta;

            if (pesoMaximo != 0 && volumeMaximo != 0)
            {
                do
                {
                    cout << "\nATENÇÃO! Ao finalizar o dia será mostrado um relatório do dia e os dados do caminhão serão excluidos, deseja continuar? (S/N)";
                    cin >> resposta;

                    if (resposta == 'S' || resposta == 's')
                    {
                        finalizarDia(pesos, valores, transporte, seguro, volumeAtual);
                        delete[] pesos;
                        delete[] valores;
                        delete[] transporte;
                        delete[] seguro;
                        pesos = nullptr;
                        valores = nullptr;
                        transporte = nullptr;
                        seguro = nullptr;
                        pesoMaximo = 0;
                        pesoAtual = 0;
                        volumeMaximo = 0;
                        volumeAtual = 0;
                        break;
                    }
                    else if (resposta == 'N' || resposta == 'n')
                    {
                        cout << "\nOperação Cancelada." << endl;
                        break;
                    }
                    else
                    {
                        cout << "\nOpção Inválida, tente novamente." << endl;
                    }
                } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');
            }
            else
            {
                cout << "\nNão é possível finalizar o dia. Você deve primeiro iniciar o dia." << endl;
            }
            break;

        case 7:
            cout << "\nSaindo do programa..." << endl;
            break;

        default:
            cout << "\nOpção inválida, tente novamente." << endl;
        }

    } while (opcao != 7);

    delete[] pesos;
    delete[] valores;
    delete[] transporte;
    delete[] seguro;

    return 0;
}