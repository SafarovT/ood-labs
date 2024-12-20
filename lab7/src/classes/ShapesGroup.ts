import {IShape} from './interfaces/IShape'
import {ICanvas} from './interfaces/ICanvas'
import type {LineStyle, FillStyle} from '../types/styles'
import type {Frame} from '../types/frame'

class ShapesGroup implements IShape {
    private shapes: IShape[]

    constructor(shapes: IShape[]) {
        this.shapes = shapes
    }

    addShape(shape: IShape) {
        this.shapes.push(shape)
    }

    removeShape(shapeToRemove: IShape) {
        this.shapes = this.shapes.filter(shape => shape !== shapeToRemove)
    }

    getFrame(): Frame {
        const frames = this.shapes.map((shape) => shape.getFrame())
        const x1 = Math.min(...frames.map((f) => f.coordinates.x))
        const y1 = Math.min(...frames.map((f) => f.coordinates.y))
        const x2 = Math.max(...frames.map((f) => f.coordinates.x + f.width))
        const y2 = Math.max(...frames.map((f) => f.coordinates.y + f.height))
        
        const coordinates = {x: x1, y: y1}
        const width = x2 - x1
        const height = y2 - y1
        return {
            coordinates,
            width,
            height,
        }
    }

    setFrame(newFrame: Frame): void {
        const oldFrame = this.getFrame()
        const scaleX = newFrame.width / oldFrame.width
        const scaleY = newFrame.height / oldFrame.height

        this.shapes.forEach((shape) => {
            const shapeFrame = shape.getFrame()
            const newShapeFrame: Frame = {
                coordinates: {
                    x: newFrame.coordinates.x + (shapeFrame.coordinates.x - oldFrame.coordinates.x) * scaleX,
                    y: newFrame.coordinates.y + (shapeFrame.coordinates.y - oldFrame.coordinates.y) * scaleY,
                },
                width: shapeFrame.width * scaleX,
                height: shapeFrame.height * scaleY,
            }
            shape.setFrame(newShapeFrame)
        })
    }

    getLineStyle(): LineStyle | null {
        const styles = this.shapes.map((shape) => shape.getLineStyle())
        if (styles.every((style) => style === styles[0])) {
            return styles[0]
        }
        return null
    }

    setLineStyle(style: LineStyle): void {
        this.shapes.forEach((shape) => shape.setLineStyle(style))
    }

    getFillStyle(): FillStyle | null {
        const styles = this.shapes.map((shape) => shape.getFillStyle())
        if (styles.every((style) => style === styles[0])) {
            return styles[0]
        }
        return null
    }

    setFillStyle(style: FillStyle): void { // сделать так чтобы стили разных фигур не зависили друг от друга
        this.shapes.forEach((shape) => shape.setFillStyle(style))
    }

    draw(canvas: ICanvas): void {
        this.shapes.forEach((shape) => shape.draw(canvas))
    }

    isComposite(): boolean {
        return true
    }
}

export {
    ShapesGroup,
}