import {ICanvas} from './interfaces/ICanvas'
import type {Point} from '../types/point'
import type {Frame} from '../types/frame'
import {Shape} from './Shape'

class Rectangle extends Shape {
    draw(canvas: ICanvas): void {
        const frame: Frame = this.getFrame()
        const leftTop: Point = frame.coordinates
        const rightTop: Point = { x: frame.coordinates.x + frame.width, y: frame.coordinates.y }
        const leftBottom: Point = { x: frame.coordinates.x, y: frame.coordinates.y + frame.height }
        const rightBottom: Point = { x: frame.coordinates.x + frame.width, y: frame.coordinates.y + frame.height }

        const fillStyle = this.getFillStyle()
        if (fillStyle?.color) {
            canvas.setFillColor(fillStyle.color)
            canvas.fillPolygon([leftTop, rightTop, rightBottom, leftBottom])
        }

        const lineStyle = this.getLineStyle()
        if (lineStyle?.color && lineStyle.thickness) {
            canvas.setLineColor(lineStyle.color)
            canvas.setLineThickness(lineStyle.thickness)
            canvas.drawLine(leftTop, rightTop)
            canvas.drawLine(rightTop, rightBottom)
            canvas.drawLine(rightBottom, leftBottom)
            canvas.drawLine(leftBottom, leftTop)
        }
    }
}

export {
    Rectangle,
}