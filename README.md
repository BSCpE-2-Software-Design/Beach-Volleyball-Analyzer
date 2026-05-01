# Beach-Volleyball-Analyzer


 CLASS DIAGRAM (not final)
 ```mermaid
classDiagram
    class MatchManager {
        +run()
        +handleClick()
    }
    
    class RallyRecorder {
        +addTouch()
        +checkViolation()
    }
    
    class ScoreKeeper {
        +addPoint()
        +isSetFinished()
    }
    
    class StatTracker {
        +recordTouch()
        +recordError()
        +printReport()
    }
    
    class GameDisplay {
        +drawScoreboard()
        +drawLog()
    }
    
    class VolleyballRules {
        +isFourTouch()
        +isDoubleTouch()
        +isGameOver()
    }
    
    MatchManager *-- RallyRecorder
    MatchManager *-- ScoreKeeper
    MatchManager *-- StatTracker
    MatchManager --> GameDisplay
    RallyRecorder --> VolleyballRules
```


SEQUENCE DIAGRAM (not final)
```mermaid
sequenceDiagram
    actor You
    participant MatchManager
    participant RallyRecorder
    participant ScoreKeeper
    participant GameDisplay

    loop Every touch in rally
        You->>MatchManager: click player + action
        MatchManager->>RallyRecorder: addTouch()
        
        alt Violation (double/4-touch)
            RallyRecorder->>ScoreKeeper: addPoint()
            RallyRecorder->>GameDisplay: showError()
            GameDisplay-->>You: "Violation! Point to other team"
        else Attack scores
            RallyRecorder->>ScoreKeeper: addPoint()
            RallyRecorder->>GameDisplay: updateScore()
            GameDisplay-->>You: "Point! Score updated"
        else Normal touch
            RallyRecorder->>GameDisplay: updateLog()
            GameDisplay-->>You: "Touch recorded"
        end
    end
```
