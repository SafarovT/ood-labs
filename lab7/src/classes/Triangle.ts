import {ICanvas} from './interfaces/ICanvas'
import {Shape} from './Shape'

class Triangle extends Shape {
    draw(canvas: ICanvas): void {
        const frame = this.getFrame()
        const points = [
            { x: frame.coordinates.x + frame.width / 2, y: frame.coordinates.y },
            { x: frame.coordinates.x, y: frame.coordinates.y + frame.height },
            { x: frame.coordinates.x + frame.width, y: frame.coordinates.y + frame.height },
        ]

        const fillStyle = this.getFillStyle()
        if (fillStyle?.color) {
            canvas.setFillColor(fillStyle.color)
        }
        const lineStyle = this.getLineStyle()
        if (lineStyle?.color && lineStyle?.thickness) {
            canvas.setLineColor(lineStyle.color)
            canvas.setLineThickness(lineStyle.thickness)
        }
        canvas.fillPolygon(points)
    }
}

export {
    Triangle,
}
