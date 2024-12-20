import {ICanvas} from './interfaces/ICanvas'
import type {Point} from '../types/point'
import type {Frame} from '../types/frame'
import {Shape} from './Shape'

class Ellipse extends Shape {
    draw(canvas: ICanvas): void {
        const frame: Frame = this.getFrame()
        const center: Point = { x: frame.coordinates.x + (frame.width / 2), y: frame.coordinates.y + (frame.height / 2) } 

        const fillStyle = this.getFillStyle()
        if (fillStyle?.color) {
            canvas.setFillColor(fillStyle.color)
            canvas.fillEllipse(center, frame.width, frame.height)
        }

        const lineStyle = this.getLineStyle()
        if (lineStyle?.color && lineStyle?.thickness) {
            canvas.setLineColor(lineStyle.color)
            canvas.setLineThickness(lineStyle.thickness)
            canvas.drawEllipse(center, frame.width, frame.height)
        }
    }
}

export {
    Ellipse,
}