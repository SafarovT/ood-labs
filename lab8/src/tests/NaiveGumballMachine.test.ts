import {
    beforeEach,
    describe,
    expect,
    test,
} from '@jest/globals'
import {GumballMachine} from '../NaiveGumballMachine'

describe('Gumball Machine', () => {
    let gumballMachine: GumballMachine

    beforeEach(() => {
        gumballMachine = new GumballMachine(5)
    })

    test('should initialize correctly with balls', () => {
        expect(gumballMachine.ToString()).toContain('Inventory: 5 gumballs')
        expect(gumballMachine.ToString()).toContain('waiting for quarter')
    })

    test('should transition from NoQuarterState to HasQuarterState', () => {
        gumballMachine.InsertQuarter()
        expect(gumballMachine.ToString()).toContain('waiting for turn of crank')
    })

    test('should reject quarter in SoldOutState', () => {
        const soldOutMachine = new GumballMachine(0)
        soldOutMachine.InsertQuarter()
        expect(soldOutMachine.ToString()).toContain('sold out')
    })

    test('should transition to SoldOutState when last gumball is dispensed', () => {
        gumballMachine = new GumballMachine(1)
        gumballMachine.InsertQuarter()
        gumballMachine.TurnCrank()
        expect(gumballMachine.ToString()).toContain('sold out')
        expect(gumballMachine.ToString()).toContain('Inventory: 0 gumballs')
    })

    test('should not dispense gumball if no quarter is inserted', () => {
        gumballMachine.TurnCrank()
        expect(gumballMachine.ToString()).toContain('waiting for quarter')
        expect(gumballMachine.ToString()).toContain('Inventory: 5 gumballs')
    })
})

describe('States', () => {
    let gumballMachine: GumballMachine

    beforeEach(() => {
        gumballMachine = new GumballMachine(5)
    })

    test('SoldOutState: should not allow turning crank', () => {
        gumballMachine = new GumballMachine(0)
        expect(gumballMachine.ToString()).toContain('sold out')

        gumballMachine.TurnCrank()
        expect(gumballMachine.ToString()).toContain('sold out')
    })

    test('NoQuarterState: should allow inserting quarter', () => {
        gumballMachine.InsertQuarter()
        expect(gumballMachine.ToString()).toContain('waiting for turn of crank')
    })

    test('HasQuarterState: should allow turning crank and dispense gumball', () => {
        gumballMachine.InsertQuarter()
        gumballMachine.TurnCrank()
        expect(gumballMachine.ToString()).toContain('Inventory: 4 gumballs')
    })

    test('HasQuarterState: should start waiting for quarter after ejecting last one', () => {
        gumballMachine.InsertQuarter()
        gumballMachine.EjectQuarter()
        expect(gumballMachine.ToString()).toContain('waiting for quarter')
    })

    test('NoQuarterState: should not allow ejecting quarter', () => {
        gumballMachine.EjectQuarter()
        expect(gumballMachine.ToString()).toContain('waiting for quarter')
    })
})

describe('GumballMachine multiple quartes functionality', () => {
    let gumballMachine: GumballMachine

    beforeEach(() => {
        gumballMachine = new GumballMachine(10)
    })

    it('should allow adding up to 5 quarters', () => {
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()

        expect(gumballMachine.ToString()).toContain('Quarters: 5')
    })

    it('should not allow adding more than 5 quarters', () => {
        for (let i = 0; i < 6; i++) {
            gumballMachine.InsertQuarter()
        }

        expect(gumballMachine.ToString()).toContain('Quarters: 5')
    })

    it('should return one quarters when ejecting', () => {
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()

        gumballMachine.EjectQuarter()

        expect(gumballMachine.ToString()).toContain('Quarters: 2')
    })

    it('should decrement quarters and dispense gumballs when turning the crank', () => {
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.TurnCrank()

        expect(gumballMachine.ToString()).toContain('Inventory: 9')
        expect(gumballMachine.ToString()).toContain('Quarters: 1')
    })

    it('should allow returning quarters if there are more quarters than gumballs', () => {
        gumballMachine = new GumballMachine(2)

        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()

        gumballMachine.TurnCrank()
        gumballMachine.TurnCrank()

        expect(gumballMachine.ToString()).toContain('Inventory: 0')
        expect(gumballMachine.ToString()).toContain('Quarters: 1')

        gumballMachine.EjectQuarter()
        expect(gumballMachine.ToString()).toContain('Quarters: 0')
    })

    it('should not allow turning the crank if there are no gumballs left', () => {
        gumballMachine = new GumballMachine(1)

        gumballMachine.InsertQuarter()
        gumballMachine.InsertQuarter()
        gumballMachine.TurnCrank()
        gumballMachine.TurnCrank()

        expect(gumballMachine.ToString()).toContain('Inventory: 0')
        expect(gumballMachine.ToString()).toContain('Quarters: 1')
    })
})
