import {ICanvas} from './interfaces/ICanvas'
import {IShape} from './interfaces/IShape'
import type {Frame} from '../types/frame'
import type {LineStyle, FillStyle} from '../types/styles'

class Shape implements IShape {
    private frame: Frame
    private lineStyle: LineStyle
    private fillStyle: FillStyle

    constructor(frame: Frame, lineStyle: LineStyle, fillStyle: FillStyle) {
        this.frame = frame
        this.lineStyle = lineStyle
        this.fillStyle = fillStyle
    }

    getFrame(): Frame {
        return this.frame
    }

    setFrame(frame: Frame): void {
        this.frame = frame
    }

    getLineStyle(): LineStyle {
        return this.lineStyle;
    }

    setLineStyle(style: LineStyle): void {
        this.lineStyle = style
    }

    getFillStyle(): FillStyle {
        return this.fillStyle
    }

    setFillStyle(style: FillStyle): void {
        this.fillStyle = style
    }

    draw(canvas: ICanvas): void {}

    isComposite(): boolean {
        return false
    }
}

export {
    Shape,
}