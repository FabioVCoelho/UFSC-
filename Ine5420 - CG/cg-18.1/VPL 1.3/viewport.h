#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "dimensions.h"

struct Viewport {
	Viewport() {}
	Viewport(const WinDims<int>& size)
        : m_size(size) {}

    void resize(const WinDims<int>& size) {
        m_size = size;
    }
    const WinDims<int>& size() {return m_size;}

private:
    WinDims<int> m_size;
};

#endif