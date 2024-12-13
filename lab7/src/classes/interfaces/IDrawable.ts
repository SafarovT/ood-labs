import {ICanvas} from './ICanvas'

abstract class IDrawable {
    abstract draw(canvas: ICanvas): void
}

export {
    IDrawable,
}
