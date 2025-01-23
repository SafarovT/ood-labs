import type {Point} from '../types/point'
import type {RGBA} from '../types/colors'
import {rgbaToString} from '../types/colors'
import {ICanvas} from './interfaces/ICanvas'

export class SVGCanvas implements ICanvas {
    private svgContent: string[]
    private currentFillColor: RGBA = {r: 0, g: 0, b: 0, a: 0} 
    private currentLineColor: RGBA = {r: 0, g: 0, b: 0, a: 0} 
    private currentLineWidth: number = 1

    constructor(private width: number, private height: number) {
        this.svgContent = [`<svg xmlns="http://www.w3.org/2000/svg" width="${width}" height="${height}">`]
    }

    setFillColor(color: RGBA): void {
        this.currentFillColor = color
    }

    setLineColor(color: RGBA): void {
        this.currentLineColor = color
    }

    setLineThickness(width: number): void {
        this.currentLineWidth = width
    }

    drawLine(start: Point, end: Point): void {
        const line = `<line x1="${start.x}" y1="${start.y}" x2="${end.x}" y2="${end.y}" stroke="${rgbaToString(this.currentLineColor)}" stroke-width="${this.currentLineWidth}" />`
        this.svgContent.push(line)
    }

    drawEllipse(center: Point, width: number, height: number): void {
        const ellipse = `<ellipse cx="${center.x + width / 2}" cy="${center.y + height / 2}" rx="${width / 2}" ry="${height / 2}" stroke="${rgbaToString(this.currentLineColor)}" stroke-width="${this.currentLineWidth}" fill="none" />`
        this.svgContent.push(ellipse)
    }

    fillEllipse(center: Point, width: number, height: number): void {
        const ellipse = `<ellipse cx="${center.x + width / 2}" cy="${center.y + height / 2}" rx="${width / 2}" ry="${height / 2}" fill="${rgbaToString(this.currentFillColor)}" stroke="none" stroke-width="0" />`
        this.svgContent.push(ellipse)
    }

    fillPolygon(points: Point[]): void {
        const pointsStr = points.map(point => `${point.x},${point.y}`).join(' ')
        const polygon = `<polygon points="${pointsStr}" fill="${rgbaToString(this.currentFillColor)}" stroke="none" stroke-width="0" />`
        this.svgContent.push(polygon)
    }

    toSvg(): string {
        return `${this.svgContent.join('')}</svg>`
    }
}
