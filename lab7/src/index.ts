import {writeFileSync} from 'fs'
import {demoShapes} from './demo'
import {SVGCanvas} from './classes/SVGCanvas'

const canvas = new SVGCanvas(1200, 900)
demoShapes(canvas)
writeFileSync('result.svg', canvas.toSvg())