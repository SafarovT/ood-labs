import {IDrawable} from './interfaces/IDrawable'
import {IShape} from './interfaces/IShape'
import {ICanvas} from './interfaces/ICanvas'

type ShapesMap = Map<string, IShape>

class Slide implements IDrawable {
    private elements: ShapesMap

    constructor(elements: ShapesMap) {
        this.elements = elements
    }

    draw(canvas: ICanvas): void {
        this.elements.forEach(el => el.draw(canvas))
    }
    
    addElement(element: IShape, id: string) {
        if (!this.elements[id]) {
            this.elements[id] = element
        }
    }
    
    getElement(id: string): Element | null {
        return this.elements[id]
    }
}

export {
    Slide,
}

export type {
    ShapesMap,
}