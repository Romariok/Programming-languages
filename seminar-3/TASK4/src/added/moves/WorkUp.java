package added.moves;
import ru.ifmo.se.pokemon.*;
public class WorkUp extends StatusMove{
    public WorkUp(){
        super(Type.NORMAL, 0, 100);
    }
    @Override
    protected void applySelfEffects(Pokemon p){
        Effect e = new Effect().stat(Stat.SPECIAL_ATTACK, +1).stat(Stat.SPECIAL_DEFENSE, +1);
        p.addEffect(e);
    }
    @Override
    protected String describe(){
        return "uses Work Up";
    }
}