interface IState {
    InsertQuarter(): void
    EjectQuarter(): void
    TurnCrank(): void
    Dispense(): void
    ToString(): string
}

interface IGumballMachine {
    ReleaseBall(): void
    GetBallCount(): number
    AddQuarter(): void
    RemoveOneQuarter(): void
    RemoveAllQuarters(): void
    GetQuarterCount(): number

    SetSoldOutState(): void
    SetNoQuarterState(): void
    SetSoldState(): void
    SetHasQuarterState(): void
}

const MAX_QUARTERS_COUNT = 5

class SoldState implements IState {
    private gumballMachine: IGumballMachine
    constructor(gumballMachine: IGumballMachine) {
        this.gumballMachine = gumballMachine
    }

    InsertQuarter(): void {
        console.log("Please wait, we're already giving you a gumball")
    }

    EjectQuarter(): void {
        if (!this.gumballMachine.GetQuarterCount()) {
            console.log("Sorry you already turned the crank")
            return
        }
        this.gumballMachine.RemoveOneQuarter()
        console.log("Ejected succussfully")
    }

    TurnCrank(): void {
        console.log("Turning twice doesn't get you another gumball")
    }

    Dispense(): void {
        this.gumballMachine.ReleaseBall()
        if (!this.gumballMachine.GetBallCount()) {
            console.log("Oops, out of gumballs")
            this.gumballMachine.SetSoldOutState()
        }
        else if (this.gumballMachine.GetQuarterCount() > 0) {
            this.gumballMachine.SetHasQuarterState()
        }
        else {
            this.gumballMachine.SetNoQuarterState()
        }
    }

    ToString(): string {
        return "delivering a gumball"
    }
}

class SoldOutState implements IState {
    private gumballMachine: IGumballMachine
    constructor(gumballMachine: IGumballMachine) {
        this.gumballMachine = gumballMachine
    }

    InsertQuarter(): void {
        console.log("You can't insert a quarter, the machine is sold out")
    }

    EjectQuarter(): void {
        console.log(`Returning ${this.gumballMachine.GetQuarterCount()} quarter(s)`)
        this.gumballMachine.RemoveAllQuarters()
    }

    TurnCrank(): void {
        console.log("You turned but there's no gumballs")
    }

    Dispense(): void {
        console.log("No gumball dispensed")
    }

    ToString(): string {
        return "sold out"
    }
}

class HasQuarterState implements IState {
    private gumballMachine: IGumballMachine

    constructor(gumballMachine: IGumballMachine) {
        this.gumballMachine = gumballMachine
    }

    InsertQuarter(): void {
        if (this.gumballMachine.GetQuarterCount() < MAX_QUARTERS_COUNT) {
            this.gumballMachine.AddQuarter()
            console.log("You inserted a quarter")
        }
        console.log("You can't insert another quarter")
    }

    EjectQuarter(): void {
        console.log("Quarter returned")
        this.gumballMachine.RemoveOneQuarter()
        if (!this.gumballMachine.GetQuarterCount()) {
            this.gumballMachine.SetNoQuarterState()
        }
    }

    TurnCrank(): void {
        console.log("You turned...")
        this.gumballMachine.SetSoldState()
        this.gumballMachine.RemoveOneQuarter()
    }

    Dispense(): void {
        console.log("No gumball dispensed")
    }

    ToString(): string {
        return "waiting for turn of crank"
    }
}

class NoQuarterState implements IState {
    private gumballMachine: IGumballMachine

    constructor(gumballMachine: IGumballMachine) {
        this.gumballMachine = gumballMachine
    }

    InsertQuarter(): void {
        console.log("You inserted a quarter")
        this.gumballMachine.AddQuarter()
        this.gumballMachine.SetHasQuarterState()
    }

    EjectQuarter(): void {
        console.log("You haven't inserted a quarter")
    }

    TurnCrank(): void {
        console.log("You turned but there's no quarter")
    }

    Dispense(): void {
        console.log("You need to pay first")
    }

    ToString(): string {
        return "waiting for quarter"
    }
}

class GumballMachine implements IGumballMachine {
    private soldState: SoldState
    private soldOutState: SoldOutState
    private noQuarterState: NoQuarterState
    private hasQuarterState: HasQuarterState

    private state: IState
    private count: number
    private quarters: number

    constructor(numBalls: number) {
        this.soldState = new SoldState(this)
        this.soldOutState = new SoldOutState(this)
        this.noQuarterState = new NoQuarterState(this)
        this.hasQuarterState = new HasQuarterState(this)

        this.quarters = 0
        this.count = numBalls
        this.state = this.count > 0
            ? this.noQuarterState
            : this.soldOutState
    }

    InsertQuarter(): void {
        this.state.InsertQuarter()
    }

    EjectQuarter(): void {
        this.state.EjectQuarter()
    }

    TurnCrank(): void {
        this.state.TurnCrank()
        this.state.Dispense()
    }

    AddQuarter(): void {
        this.quarters++
    }

    RemoveOneQuarter(): void {
        this.quarters--
    }

    RemoveAllQuarters(): void {
        this.quarters = 0
    }

    ToString(): string {
        return `
Mighty Gumball, Inc.
TypeScript-enabled Standing Gumball Model
Inventory: ${this.count} gumball${this.count !== 1 ? 's' : ''}'
Quarters: ${this.quarters}
Machine is ${this.state.ToString()}
        `
    }

    ReleaseBall(): void {
        if (this.count !== 0) {
            console.log("A gumball comes rolling out the slot...")
            this.count--
        }
    }

    GetBallCount(): number {
        return this.count
    }

    GetQuarterCount(): number {
        return this.quarters
    }

    SetSoldOutState(): void {
        this.state = this.soldOutState
    }

    SetNoQuarterState(): void {
        this.state = this.noQuarterState
    }

    SetSoldState(): void {
        this.state = this.soldState
    }

    SetHasQuarterState(): void {
        this.state = this.hasQuarterState
    }
}

export {
    IGumballMachine,
    GumballMachine,
}
