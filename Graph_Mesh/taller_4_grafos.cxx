#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Graph.h"

// -------------------------------------------------------------------------


// -------------------------------------------------------------------------

// TODO 1: typedef Graph< Point, float > TGraph 
Graph<Point> graph;


// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 4 )
  {
    std::cerr
      << "Usage: " << argv[ 0 ] << " input_mesh start end"
      << std::endl;
    return( 1 );

  } // fi
  long start_id = std::atoi( argv[ 2 ] );
  long end_id = std::atoi( argv[ 3 ] );

  // -----------------TODO 2: TGraph g; -------------------//
  //Se marca el grafo como no dirigido con el setDirected
  graph.setDirected(false);

  //Como el grafo es un map, no se puede acceder por índice, así que se utilizará un vector auxiliar para poder acceder
  //a los puntos teniendo en cuenta (x0, y0, z0).
  std::vector<Point> puntos_indice;

  // Load file in a buffer
  std::ifstream in_mesh_stream( argv[ 1 ], std::ifstream::binary );
  if( !in_mesh_stream )
  {
    std::cerr << "Error reading \"" << argv[ 1 ] << "\"" << std::endl;
    return( 1 );

  } // fi
  in_mesh_stream.seekg( 0, in_mesh_stream.end );
  unsigned long in_mesh_file_length = in_mesh_stream.tellg( );
  in_mesh_stream.seekg( 0, in_mesh_stream.beg );
  char* in_mesh_file_buffer = new char[ in_mesh_file_length ];
  in_mesh_stream.read( in_mesh_file_buffer, in_mesh_file_length );
  in_mesh_stream.close( );
  std::istringstream in_mesh( in_mesh_file_buffer );

  // Read vertices
  long nPoints;
  in_mesh >> nPoints;
  for( long pId = 0; pId < nPoints; pId++ )
  {
    Point pnt;
    in_mesh >> pnt.X >> pnt.Y >> pnt.Z;
    puntos_indice.push_back(pnt);

    // ------------------TODO 3: g.AddVertex( pnt ); --------------------------------
    //Aquí se añade el vertice con a funcion addNode del grafo
    //Parametros: pnt, el cual es de tipo Point
    graph.addNode(pnt);

  } // rof

  // Read edges
  long nEdges;
  in_mesh >> nEdges;
  for( long eId = 0; eId < nEdges; eId++ )
  {
    long start, end;
    in_mesh >> start >> end;

    /*
      TODO 4:
      cost = g.GetVertex( start ).distanceTo( g.GetVertex( end ) );
      g.AddEdge( start, end, cost );
      g.AddEdge( end, start, cost );
    */
    //Para poder calcular la distancia entre los dos puntos se hace uso del vector auxiliar para no tener problemas con los índices
    //Se accede entonces a la posicion (start) del vector para obtener el Point y se calcula la distancia al punto final
    Point p_start = puntos_indice[start];
    Point p_end = puntos_indice[end];
    float cost = p_start.distanceTo(p_end);

    //En el TAD Graph en la fnción de addEdge se implementó la lógica para añadir arista de acuerdo si el grafo es dirigido o no
    //para saber si la arista se añade en un solo sentido o dos (Ver funcion addEdge de Graph.hxx)
    //Esto se puede hacer ya que el grafo tiene un setDirected que permite saber cómo manejar las operaciones en tiempo de ejecución de acuerdo al tipo de grafo
    graph.addEdge(p_start, p_end, cost);

  } // rof
  delete [] in_mesh_file_buffer;
  //Como vertices no está definido entonces hay un error, entonces se utilizará el tamaño del vector auxiliar de puntos_indice
  /*
  if(
    start_id < 0 || start_id >= vertices.size( ) ||
    end_id < 0 || end_id >= vertices.size( )
    )
  */
  if(
    start_id < 0 || start_id >= puntos_indice.size( ) ||
    end_id < 0 || end_id >= puntos_indice.size( )
    )
  {
    std::cerr << "Invalid path endpoints." << std::endl;
    return( 1 );

  } // fi

  /*
    TODO 5:
    std::vector< long > path = g.Dijkstra( start_id, end_id );
    std::cout << path.size( ) << std::endl;
    for( unsigned int i = 0; i < path.size( ); ++i )
    std::cout
    << vertices[ path[ i ] ].X << " "
    << vertices[ path[ i ] ].Y << " "
    << vertices[ path[ i ] ].Z << std::endl;
  */
  
  /*Se pasan a la función de dijkstra el punto de inicio y el punto final
    Se podrían mandar el start_id y el end_id pero para acceder a los puntos del grafo
    mediante el índice se tendría que pasar el vector auxiliar lo cual es innecesario 
  */
  std::vector<Point> path = graph.Dijkstra(puntos_indice[start_id], puntos_indice[end_id]);
  //Para poder mostrar los indices y el path:
  std::cout << path.size( ) << std::endl;

    // Iteramos sobre el vector de Puntos (path) que nos devolvió Dijkstra
    for( unsigned int i = 0; i < path.size( ); ++i ) {
        std::vector<Point>::iterator it = std::find(puntos_indice.begin(), puntos_indice.end(), path[i]);

        if (it != puntos_indice.end()) {
            // Calculamos la distancia (índice) desde el inicio del vector
            long index = std::distance(puntos_indice.begin(), it);

            // Imprimimos el índice del punto
            std::cout << index << std::endl; 
        }
    }
  return( 0 );
}

// eof -
