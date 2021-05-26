//
// Created by pedro on 19/05/2021.
//

#ifndef E_ESTAFETAS_ALGORITHMS_H
#define E_ESTAFETAS_ALGORITHMS_H

#include "Connectivity.h"
#include "utils.h"

extern Company<int> company;
extern Graph<int> graph;



template<class T>       // Algoritmo utilizado na Fase 4 - Vários carros atendem vários requests, considerando carga (limite de requests)
vector<Vertex<T>*> alg(Car<T> *car, vector<Request<T>*> &requests) {
    vector<T> stores;       // Este vetor vai conter os stores para os quais o car se pode dirigir (é inicializado com todos os stores que estão nos requests)
    vector<T> clients;           // Este vetor vai conter os clients para os quais o car se pode dirigir, isto é, aqueles que o car já requisitou o pedido na loja que eles pediram (é vazio inicialmente)
    vector<Vertex<T> *> result;  // Este vetor vai conter os pontos de interesse pela ordem em que o car os vai percorrer (stores e clients)

    // -------------------------------------------- Algoritmo de cálculo do vetor ordenado dos pontos de interesse percorridos pelo car --------------------------------------------

    // Inicializa o vetor stores com todos os stores que estão presentes nos requests
    for (Request<T> *request : requests) {
        stores.push_back(request->getStore()->getNodeID());
    }




    double battery = car->getBattery();
    while (!stores.empty() || !clients.empty()) {


        if (result.empty()) { //Primeira iteraçao, ir buscar a loja mais proxima
            T nearest_store = get_NearestStore<T>(company.getParque(), stores);

            Request<T>* requestanalyse = findRequest(nearest_store, requests);

            T cliente_loja = requestanalyse->getClient()->getNodeID();


            erase(nearest_store, stores);
            vector<Vertex<T> *> auxresult;

            auxresult.push_back(graph.findVertex(nearest_store));
            auxresult.push_back(graph.findVertex(cliente_loja));


            if (get_path_distance(auxresult) < battery) {

                requests.erase(find(requests.begin(), requests.end(), requestanalyse));
                clients.push_back(cliente_loja);
                result.push_back(graph.findVertex(nearest_store));
                requestanalyse->setcar(car);
            }
        }else{
            T menor;
            if(!clients.empty())
                menor = clients[0];
            else{
                menor = get_NearestStore<T>(result.back()->getInfo(), stores);
            }

            double menor_distance = calculate_special_distance(result.back()->getInfo(), menor);

            for (T point : stores){
                if ( calculate_special_distance(result.back()->getInfo(), point) < menor_distance ){
                    menor_distance =calculate_special_distance(result.back()->getInfo(), point);
                    menor = point;
                }
            }
            for (T point : clients){
                if ( calculate_special_distance(result.back()->getInfo(), point) < menor_distance ){
                    menor_distance =calculate_special_distance(result.back()->getInfo(), point);
                    menor = point;
                }
            }


            if(is_in( menor , stores)) {
                T cliente_loja = findRequest(menor, requests)->getClient()->getNodeID();
                erase(menor, stores);
                vector<T> auxordering;

                vector<T> auxclient;
                auxclient.push_back(cliente_loja);
                for (T c : clients)
                    auxclient.push_back(c);

                while (!auxclient.empty()){  //ordena os clientes que falta atender para fazer o percurso
                    auto ptr = auxclient.begin();
                    auto ftr = auxclient.end();
                    double menor_dist = 100000;
                    vector<int>::iterator menor_it;

                    for (ptr; ptr < ftr; ptr++){
                        if (calculate_special_distance(result.back()->getInfo(), *ptr) < menor_dist) {
                            menor_dist = calculate_special_distance(result.back()->getInfo(), *ptr);
                            menor_it = ptr;
                        }
                    }

                    auxclient.erase(menor_it);
                    auxordering.push_back(*menor_it);
                }

                vector<Vertex<T>*> auxresult;
                for( Vertex<T>* v : result){
                    auxresult.push_back(v);
                }

                auxresult.push_back(graph.findVertex(menor));

                for( T v : auxordering){
                    auxresult.push_back(graph.findVertex(v));
                }


                if ((get_path_distance(auxresult) < battery)) {

                    Request<T>* requestanalyse = findRequest(menor, requests);

                    requestanalyse->setcar(car);


                    requests.erase(find(requests.begin(), requests.end(), requestanalyse));

                    clients.push_back(cliente_loja);
                    result.push_back(graph.findVertex(menor));
                }
            }
            else{
                vector<Vertex<T> *> auxresult;
                for( Vertex<T>* v : result){
                    auxresult.push_back(v);
                }
                erase(menor, clients);
                auxresult.push_back(graph.findVertex(menor));

                Vertex<T>* m_v = graph.findVertex(menor);
                if ((get_path_distance(auxresult) < battery) && (!isIn(m_v, result))) {
                    result.push_back(graph.findVertex(menor));
                }
            }
        }
    }

// -------------------------------------------- Fim do Algoritmo --------------------------------------------

    vector<Vertex<T> *> percurso = {};        // Vai conter o percurso completo do car

    if (!result.empty()) {
        T init = result[0]->getInfo();
        T final;
        graph.dijkstraShortestPath(company.getParque());
        vector<Vertex<T> *> vetor = graph.getPath(company.getParque(), init);
        percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
        bool inicio = true;

        for (Vertex<T> *vertex : result) {
            if (inicio) {
                inicio = false;
                continue;
            }

            final = vertex->getInfo();
            graph.dijkstraShortestPath(init);
            vetor = graph.getPath(init, final);
            percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);

            init = final;

            if (result.back()->getInfo() == vertex->getInfo()) {
                graph.dijkstraShortestPath(init);
                final = company.getParque();
                vetor = graph.getPath(init, final);
                percurso.insert(percurso.end(), vetor.begin(), vetor.end());
            }

        }
        percurso.push_back(graph.findVertex(final));
    }



    return percurso;
}


template <class T>// Vários carros atendem vários pedidos, agora considerando carga (limite de pedidos)
void Varios_Carros_Com_Autonomia() {

    cout << "\n\n\t\t     Atendimento de varios Pedidos por varios Carros, com carga limitada \n\n";
    int nc = 1, nr = 1, ne = 1;
    cout << "Clientes:" << endl;
    for (Client<T> *client : company.getClients()) {
        cout << " [" << nc << "]" << client->getName() << endl;
        nc++;
    }
    cout << endl << "Lojas:" << endl;
    for (Store<T> *store : company.getStores()) {
        cout << " [" << nr << "]" << store->getName() << endl;
        nr++;
    }

    vector<Request<T>*> requests;
    Client<T>* client;
    Store<T>* store;
    int nclient, nstore;
    do {
        do {
            cout << "\nCliente que deseja efetuar o pedido: ";
            cin.clear();
            cin >> nclient;
            cin.ignore(1000, '\n');
        } while (nclient < 0 || nclient > company.getNumClients());
        if (nclient != 0)
            client = company.getClients().at(nclient - 1);
        do {
            cout << "\nLoja desejada: ";
            cin.clear();
            cin >> nstore;
            cin.ignore(1000, '\n');
        } while (nstore < 0 || nstore > company.getNumStores());
        if (nstore != 0)
            store = company.getStores().at(nstore - 1);
        if (nclient != 0 && nstore != 0) {
            Request<T>* request = new Request<T>(client, store);
            requests.push_back(request);
        }
    } while (nclient != 0 && nstore != 0);

    // Neste ponto, temos todos os dados de input, nomeadamente a lista de request esfetuados pelo utilizador

    vector<Vertex<T>*> percurso;        // Armazena o percurso de cada estafeta
    vector<vector<Vertex<T>*>> percursos;       // Lista dos percursos dos vários carros
    vector<Request<T>*> pedidos_impossiveis;

    //
    for(Request<T>* request : requests) {

        //Verificar se existe caminho com uma pesquisa em profundidade:
        Vertex<T>* v_parque=graph.findVertex(company.getParque());
        Vertex<T>* v_store=graph.findVertex(request->getStore()->getNodeID());
        Vertex<T>* v_client=graph.findVertex(request->getClient()->getNodeID());
        vector<Vertex<T>*> caminho_conexo_e = dfs(&graph, v_parque);
        vector<Vertex<T>*> caminho_conexo_s = dfs(&graph, v_store);
        vector<Vertex<T>*> caminho_conexo_c = dfs(&graph, v_client);

        if(!isIn(v_store, caminho_conexo_e) || !isIn(v_client, caminho_conexo_s) || !isIn(v_parque, caminho_conexo_c)){
            pedidos_impossiveis.push_back(request);

        }
    }
    if(pedidos_impossiveis.size()!=0){
        for(Request<T>* ped : pedidos_impossiveis){
            erase_request(ped,requests);
        }
        cout<<"\nLamentamos, existem "<<pedidos_impossiveis.size()<<" request que nao podem ser efetuados:"<<endl;
    }

    for(Request<T>* reqa : pedidos_impossiveis){
        cout << "Cliente: " << reqa->getClient()->getName() << " - Loja: " << reqa->getStore()->getName() << endl;
    }



    cout << endl;



    // Calcular o percurso de cada estafeta
    company.setRequests(requests);
    vector<Request<T>*> aux = company.getRequests();

    if(!aux.empty()) {

        for (Car<T> *car: company.getCars()) {

            percurso = alg(car, aux);

            if (!percurso.empty()) {
                percursos.push_back(percurso);

                cout << "Carro - " << car->getName() << " - bateria : " << car->getBattery()
                     << " - distancia do percurso : "
                     << get_distance(percurso) << endl;
            }
            if (aux.empty())
                break;
        }

        showMultiplePathsGV(percursos);     // Mostra os vários percursos dos carros
    } else {
        cout << "Nao conseguimos fazer nenhum percurso.";
        exit(0);
    }


}

#endif //E_ESTAFETAS_ALGORITHMS_H
