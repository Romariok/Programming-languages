package added.pokemon;

import ru.ifmo.se.pokemon.*;
import added.moves.LavaPlume;
import added.moves.Confide;
import added.moves.Flamethrower;
import added.moves.ScaryFace;

public class Heatran extends Pokemon{
    public Heatran (String name, int level){
        super(name, level);
        setStats(91, 90, 106, 130, 106, 77);
        setType(Type.FIRE, Type.STEEL);
        setMove(new LavaPlume(), new Confide(), new Flamethrower(), new ScaryFace());


    }
}
