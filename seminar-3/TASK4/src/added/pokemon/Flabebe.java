package added.pokemon;

import ru.ifmo.se.pokemon.*;
import added.moves.Rest;
import added.moves.CalmMind;
public class Flabebe extends Pokemon{
    public Flabebe(String name, int level){
        super(name, level);
        setStats(44, 38, 39, 61, 79, 42);
        setType(Type.FAIRY);
        setMove(new Rest(), new CalmMind());
    }
}
