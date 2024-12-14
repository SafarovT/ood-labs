import type {Frame} from '../../types/frame'
import type {FillStyle, LineStyle} from '../../types/styles'
import {IDrawable} from './IDrawable'

abstract class IShape extends IDrawable {
    abstract getFrame(): Frame
    abstract setFrame(frame: Frame): void

    abstract getLineStyle(): LineStyle | null
    abstract setLineStyle(style: LineStyle): void

    abstract getFillStyle(): FillStyle | null
    abstract setFillStyle(style: FillStyle): void

    abstract isComposite(): boolean
}

export {
    IShape,
}