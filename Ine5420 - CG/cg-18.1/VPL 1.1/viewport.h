#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "dimensions.h"

struct Viewport {
	Viewport() {}
	Viewport(const Dims2d<int>& size) 
        : m_size(size) {}

    void resize(const Dims2d<int>& size) {
        m_size.copy(size);
    }
    const Dims2d<int>& size() {return m_size;}

private:
    Dims2d<int> m_size;
};

#endif