#ifndef LAYER_H_DEFINED
#define LAYER_H_DEFINED

class Level;

class Layer
{
public:
    virtual ~Layer() {}

    virtual void render() = 0;
    virtual void update(Level* pLevel) = 0;
};

#endif
