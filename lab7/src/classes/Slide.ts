import {IDrawable} from './interfaces/IDrawable'
import {IShape} from './interfaces/IShape'
import {ICanvas} from './interfaces/ICanvas'

type ShapesMap = Map<string, IShape>

class Slide implements IDrawable {
    private elements: ShapesMap = new Map()

    draw(canvas: ICanvas): void {
        this.elements.forEach(el => {el.draw(canvas)})
    }
    
    addElement(id: string, element: IShape) {
        if (!this.elements.has(id)) {
            this.elements.set(id, element)
        }
    }
    
    getElement(id: string): IShape | null {
        return this.elements.has(id)
            ? this.elements.get(id) as IShape
            : null
    }
}

export {
    Slide,
}

export type {
    ShapesMap,
}