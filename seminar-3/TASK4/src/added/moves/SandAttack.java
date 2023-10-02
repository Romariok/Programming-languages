package added.moves;
import ru.ifmo.se.pokemon.*;
public class SandAttack extends StatusMove{
    public SandAttack(){
        super(Type.GROUND, 0, 100);
    }
    @Override
    protected void applyOppEffects(Pokemon p){
        if (!p.hasType(Type.FLYING)){
            Effect e = new Effect().stat(Stat.ACCURACY, -1);
            p.addEffect(e);
        }
    }
    @Override
    protected String describe(){
        return "uses Sand Attack";
    }
}
