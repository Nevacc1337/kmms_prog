#include "sim.hpp"
#include "second_level.hpp"
#include "third_level.hpp"
#include "fourth_level.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstring>
using namespace biv;
using UI = UserInput;

static const UI RIGHT = UI::MAP_LEFT, LEFT = UI::MAP_RIGHT;

static void takeoff(Sim& s){ int n=0; while(s.mario->get_vspeed()>=0 && n<10){ s.step(UI::MARIO_JUMP); n++; } }
static void run(Sim& s,int kind,int k){
	switch(kind){
	case 0: for(int i=0;i<k;i++) s.step(RIGHT); break;
	case 1: takeoff(s); for(int i=0;i<k;i++) s.step(RIGHT); break;
	case 2: for(int i=0;i<k;i++) s.step(UI::NO_INPUT); break;
	case 3: for(int i=0;i<k;i++) s.step(LEFT); break;
	case 4: takeoff(s); for(int i=0;i<k;i++) s.step(UI::NO_INPUT); break;
	case 5: takeoff(s); for(int i=0;i<k;i++) s.step(LEFT); break;
	}
}
struct Res{ int ok; int levels; float dist; };
static float dist(Sim& s){ return s.game.static_objs.back()->get_x() - s.mario->get_x(); }

struct M{int kind,k;};
static std::vector<M> macros(){
	std::vector<M> v;
	for(int k: {1,3,6}) v.push_back({0,k});
	for(int k=4;k<=46;k++) v.push_back({1,k});
	for(int k: {2,6,12}) v.push_back({2,k});
	for(int k: {3,8}) v.push_back({3,k});
	v.push_back({4,0});
	for(int k: {5,10}) v.push_back({5,k});
	return v;
}

Res eval(Sim& s, M m){
	int fd[2]; pipe(fd);
	pid_t p=fork();
	if(p==0){
		int d0=s.deaths; int l0=s.levels_done;
		run(s,m.kind,m.k);
		run(s,2,60);
		Res r{ s.deaths==d0, s.levels_done-l0, dist(s)};
		write(fd[1],&r,sizeof r); _exit(0);
	}
	Res r{0,0,1e9}; read(fd[0],&r,sizeof r); close(fd[0]); close(fd[1]); waitpid(p,0,0); return r;
}

GameLevel* mk1(UIFactory*f){return new FirstLevel(f);} 
GameLevel* mk2(UIFactory*f){return new SecondLevel(f);} 
GameLevel* mk3(UIFactory*f){return new ThirdLevel(f);} 
GameLevel* mk4(UIFactory*f){return new FourthLevel(f);} 

int main(int argc,char**argv){
	int lv=atoi(argv[1]); int target=argc>2?atoi(argv[2]):1; bool verbose=argc>3;
	GameLevel*(*mk[])(UIFactory*)={0,mk1,mk2,mk3,mk4};
	Sim s(mk[lv]);
	auto ms=macros();
	int stuck=0; float best=dist(s);
	while(s.levels_done<target && !s.game.is_finished() && s.frame<60000){
		int bi=-1; Res br{0,0,1e9};
		for(size_t i=0;i<ms.size();i++){
			Res r=eval(s,ms[i]);
			if(!r.ok) continue;
			bool better = bi<0 || r.levels>br.levels || (r.levels==br.levels && r.dist<br.dist-0.01f);
			if(better){bi=i;br=r;}
		}
		if(bi<0){ // no safe macro: take most-progress anyway
			if(verbose){ s.dump(); }
			printf("NO SAFE MOVE at frame %d (dist %.1f) - bot stuck\n", s.frame, dist(s)); return 2; }
		run(s,ms[bi].kind,ms[bi].k);
		float d=dist(s);
		if(d<best-0.5f){best=d;stuck=0;} else stuck++;
		if(stuck>400){ printf("STUCK at frame %d dist %.1f\n",s.frame,d); if(verbose)s.dump(); return 3; }
	}
	printf("level %d: levels_done=%d deaths=%d frames=%d finished=%d score=%d\n",lv,s.levels_done,s.deaths,s.frame,(int)s.game.is_finished(),s.game.get_score());
	return s.levels_done>=target?0:1;
}
