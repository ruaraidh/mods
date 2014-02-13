#include "depsignal.h"
#include "signal.h"
#include "partial.h"
#include "model.h"

depsignal::depsignal(string name, model* mod) : signal(name, "depsignal"), mod(mod){
  set_value(0.0);
}

void depsignal::update(double time){

  if (mod){
    mod->update(time);
  }
  else{
    cerr << "ERROR: attempt to update depsignal with NULL model pointer" <<endl;
  }
}

string depsignal::source_mod(){
  return mod->m_name;
}

vector<double> depsignal::get_partial_values(){
  vector<double> t;
  for (int i = 0; i != m_partials.size();++i){ 
    t.push_back(m_partials[i]->getVal());
  }
  return t;
}

vector<string> depsignal::get_partial_SB(){
  vector<string> t;
  for (int i = 0; i != m_partials.size();++i){ 
    t.push_back(m_partials[i]->getSB()->m_name);
  }
  return t;
}


void depsignal::add_partial(signal* other, double  value){
  signal* sig1 = static_cast<signal*>(this);
  signal* sig2 = static_cast<signal*>(other);
  m_partials.push_back(new partial(sig1,sig2,value));
}

void depsignal::clear_partials(){
  m_partials.clear();
}

void depsignal::chain_partials(){
  // apply chain  rule for this signal
  // ---------------------------------
  // so      : this signal
  // si      : an input signal of this signals model (in vector mod->m_inp[n]) for some n
  // sj      : an input signal of si (in vector (mod->m_inp[n])->m_partial) for some n
  // dso_dsi : partials in this depsignal wrt si
  // dsi_dsj : partials in signal si
  // dso_dsj = dso_dsi*dsi_dsj : put this into p vector
  //                           : once the si and sj have been processed
  //                           : like this check all sj are parameters

  signal* so = this;

  vector<partial*> p;

  for (int i = 0; i != m_partials.size();++i)
    { 

      partial* dso_dsi = m_partials[i];
      depsignal* si= dynamic_cast<depsignal*>(dso_dsi->getSB());
      parameter* pi= dynamic_cast<parameter*>(dso_dsi->getSB());
      if (si) // si is a dependent signal
	{
	  for (int j = 0 ; j != (si->m_partials).size() ; ++j)
	    { 
	      partial* dsi_dsj = si->m_partials[j];
	      signal* sj       = dsi_dsj->getSB();
	      p.push_back(new partial(so,sj,dso_dsi->getVal() * dsi_dsj->getVal()));
	    }
	}
      else if(pi) // si is an independent signal
	{ 
	  signal* lsi = dso_dsi->getSB();
	  p.push_back(new partial(so,lsi,dso_dsi->getVal()));
	}
      else
	{
	  // don't do anything for a constant
	}
  }

  if (p.empty())
    {
      // nothing to do, so just fall out here
      return;
    }

  m_partials.clear();
  m_partials.push_back(p[0]);
   for (int i = 1; i != p.size() ; ++i)
    { 
      for (int j = 0; j != m_partials.size() ; ++j)
	{
	  
	  if (p[i]->getSB() == m_partials[j]->getSB())
	    {
	       m_partials[j]->setVal(m_partials[j]->getVal() + p[i]->getVal());
	      break;	  
	    }

	  if (j == m_partials.size()-1)
	    {
	      m_partials.push_back(p[i]);
	      break;
	    } 
	} 
    }
  p.clear();
}
