#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	explicit Entity(unsigned int id) :id(id) {}
	unsigned int getId() const { return id; }

private:
	unsigned int id;
};
#endif//ENTITY_H