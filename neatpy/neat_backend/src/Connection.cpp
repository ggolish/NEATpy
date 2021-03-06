
#include "Connection.h"
#include "Node.h"
#include "Genome.h"
#include "utilities.h"
#include "options.h"

// Creates a new connection from fnode to tnode, with a random
// weight 
Connection::Connection(Node *fnode, Node *tnode, int innov) :
  from_node(fnode), to_node(tnode), innovation_number(innov), disabled(false)
{
  // Ensure each nodes' connection pointers are correct
  from_node->out_connections.push_back(this);
  to_node->in_connections.push_back(this);
  // Generate a random weight for this connection from a uniform distribution
  weight = neat_random::uniform(neat_options::MIN_CONNECTION_WEIGHT,
                                neat_options::MAX_CONNECTION_WEIGHT);
}

// Creates a new connection from fnode to tnode with a weight
// equal to weight
Connection::Connection(Node *fnode, Node *tnode, int innov, double weight) :
  from_node(fnode), to_node(tnode), innovation_number(innov), weight(weight), disabled(false)
{
  // Ensure each nodes' connection pointers are correct
  from_node->out_connections.push_back(this);
  to_node->in_connections.push_back(this);
}

Connection *Connection::copy(Genome *new_g)
{
  Node *new_from, *new_to;
  for(auto n = new_g->nodes.begin(); n != new_g->nodes.end(); ++n) {
    if((*n)->innovation_number == from_node->innovation_number)
      new_from = (*n);
    if((*n)->innovation_number == to_node->innovation_number)
      new_to = (*n);
  }
  Connection *c = new Connection(new_from, new_to, innovation_number, weight);
  c->disabled = disabled;
  return c;
}

std::ostream &operator<<(std::ostream &os, const Connection &conn)
{
    os << "<Connection " << &conn << " ";
    os << "innov=" << conn.innovation_number << " ";
    os << "from_node=" << conn.from_node << " ";
    os << "to_node=" << conn.to_node << " ";
    os << "weight=" << conn.weight << " ";
    os << "disabled=" << conn.disabled;
    os << ">";
    return os;
}
