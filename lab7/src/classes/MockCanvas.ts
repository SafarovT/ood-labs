import type {Point} from '../types/point'
import type {RGBA} from '../types/colors'
import {ICanvas} from './interfaces/ICanvas'

class MockCanvas implements ICanvas {
    drawLine(start: Point, end: Point): void {
        console.log(`Draw line: (${start.x}, ${start.y}) to (${end.x}, ${end.y})`)
    }

    drawEllipse(center: Point, width: number, height: number): void {
        console.log(`Draw ellipse at (${center.x}, ${center.y}) with width ${width} and height ${height}`)
    }

    fillEllipse(center: Point, width: number, height: number): void {
        console.log(`Fill ellipse at (${center.x}, ${center.y}) with width ${width} and height ${height}`)
    }

    fillPolygon(points: Point[]): void {
        console.log(`Fill polygon with points: ${JSON.stringify(points)}`)
    }

    setFillColor(color: RGBA): void {
        console.log(`Set fill color: rgba(${color.r}, ${color.g}, ${color.b}, ${color.a})`)
    }

    setLineColor(color: RGBA): void {
        console.log(`Set line color: rgba(${color.r}, ${color.g}, ${color.b}, ${color.a})`)
    }

    setLineThickness(thickness: number): void {
        console.log(`Set line thickness: ${thickness}`)
    }
}

export {
    MockCanvas,
}