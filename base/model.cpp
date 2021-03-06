#include "base.h"
#include "model.h"
#include "config.h"
#include "value.h"
#include "constant.h"
#include "parameter.h"
#include "depsignal.h"

dictionary<model> model::dict;

model::model(string name, string class_name) : base(name, class_name){
  dict.add(name, this);
  m_connect = false;
  update_status(true);
}

void model::createSig(const string &sig){
  m_out.push_back(new depsignal(sig,this));
}


//
// connect to another model in the config file
// 
model* model::connectmod( const string &property){
  model* other;
  config conf;
  std::string strname = conf.get_name(m_class_name,m_name,property); 
  if (other = dict.get(strname))
    {
      other->connect();
      for(int i = 0 ; i < (other->m_out).size() ; ++i){
	m_inp.push_back(other->m_out[i]);
	cout  << m_name << " connected to " << (other->m_out[i])->m_name <<endl;
      }
    }
  else
    {
      cerr << "Error: unable to connect model " << m_name 
	   << " as requested (model " << strname << " not defined in config)" << endl;
      std::exit(1);
    }
  return other; 
}
//
// for connectpar config entries can be parameters or double constants
//
void model::connectpar( const string &property){
  config conf;
  value* val = conf.get_value(m_class_name,m_name,property);

  if (name_value* sv = dynamic_cast< name_value*>(val))
    {
      if (parameter* par = parameter::dict.get(sv->get_value()))
	{
	  // config entry is a parameter
	  m_inp.push_back(par);
	  cout  << m_name << " connected to parameter with value "<< par->get_value() <<endl;
	}
      else
	{
	  cerr << "Error: unable to connect model to " << m_name 
               << " (property " << sv->get_value() << " not defined)" << endl;
	  std::exit(1);
	}
    }
  else if (double_value* dv = dynamic_cast< double_value*>(val))
    {
      m_inp.push_back(new constant(dv->get_value()));
      cout  << m_name << " connected to constant with value "<< dv->get_value() << endl;
    }
    else
    {
      cerr << "Error: unexpected type found when trying to connect  model to " << property <<endl;
      std::exit(1);
    }
}

void model::initialiseVectors(){
  so.assign(m_out.size(),0.0);
  si.assign(m_inp.size(),0.0);
  std::vector<double> s;
  s.assign(m_inp.size(),0.0);
  for (int i = 0; i < m_out.size();++i){
    dso_dsi.push_back(s);
  }
  std::vector<string> t;
  t.assign(m_inp.size(),"");
  for (int i = 0; i < m_out.size();++i){
    si_name.push_back(t);
  }
}

void model::update_inp(double time){
  // m_status = false;
  for(int  i = 0; i < m_inp.size(); ++i){
    m_inp[i]->update(time);
    if (m_inp[i]->update_status() == true ) 
      {
      	m_status = true;
      }
    si[i] = m_inp[i]->get_value();
  }
}

bool model::update_status(){
  return m_status;
}

void model::update_status(bool stat){
  // update model status and output signal status
  for(int  i = 0; i < m_out.size(); ++i){
    m_out[i]->update_status(stat);
  }
  m_status = stat;
}

void model::chain_partials(){
  for (int i = 0 ; i < so.size() ; ++i)
    {
      m_out[i]->set_value(so[i]); 

      m_out[i]->clear_partials();       // clean up output signals
    }
  this->update_status(true);           // set model status to updated (true)

  for (int i = 0 ; i < so.size() ; ++i)
    {
      for (int j = 0 ; j < si.size() ; ++j)
	{
	  m_out[i]->add_partial( m_inp[j] , dso_dsi[i][j] );  // add partials wrt input signals
	}
      m_out[i]->chain_partials();  // perform chain rule to leave only independent signals

      dso_dsi[i].clear();  // clean up partials vector
      si_name[i].clear();  // clean up input vector

      
      std::vector<double>  vals = m_out[i]->get_partial_values();
      std::vector<string>  nams = m_out[i]->get_partial_SB();
      for(int j = 0 ; j < vals.size(); ++j)
	{
	  dso_dsi[i].push_back(vals[j]);        // update partials vector
	  si_name[i].push_back(nams[j]);        // update names of input signals
	}
    }
}

