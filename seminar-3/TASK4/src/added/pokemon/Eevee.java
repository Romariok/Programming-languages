package added.pokemon;

import ru.ifmo.se.pokemon.*;
import added.moves.QuickAttack;
import added.moves.SandAttack;
import added.moves.WorkUp;
public class Eevee extends Pokemon {
    public Eevee(String name, int level){
        super(name, level);
        setStats(55, 55, 50, 45, 65, 55);
        setType(Type.NORMAL);
        setMove(new QuickAttack(), new SandAttack(), new WorkUp());
    }
}
