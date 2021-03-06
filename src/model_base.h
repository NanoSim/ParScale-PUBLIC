/*------------------------------------------------------------------------------------*\

                                      /$$$$$$                      /$$          
                                     /$$__  $$                    | $$          
        /$$$$$$   /$$$$$$   /$$$$$$ | $$  \__/  /$$$$$$$  /$$$$$$ | $$  /$$$$$$ 
       /$$__  $$ |____  $$ /$$__  $$|  $$$$$$  /$$_____/ |____  $$| $$ /$$__  $$
      | $$  \ $$  /$$$$$$$| $$  \__/ \____  $$| $$        /$$$$$$$| $$| $$$$$$$$
      | $$  | $$ /$$__  $$| $$       /$$  \ $$| $$       /$$__  $$| $$| $$_____/
      | $$$$$$$/|  $$$$$$$| $$      |  $$$$$$/|  $$$$$$$|  $$$$$$$| $$|  $$$$$$$
      | $$____/  \_______/|__/       \______/  \_______/ \_______/|__/ \_______/
      | $$                                                                      
      | $$                                                                      
      |__/        A Compilation of Particle Scale Models

   Copyright (C): 2014 DCS Computing GmbH (www.dcs-computing.com), Linz, Austria
                  2014 Graz University of Technology (ippt.tugraz.at), Graz, Austria
---------------------------------------------------------------------------------------
License
    ParScale is licensed under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).

    Everyone is permitted to copy and distribute verbatim copies of this license
    document, but changing it is not allowed.

    This version of the GNU Lesser General Public License incorporates the terms
    and conditions of version 3 of the GNU General Public License, supplemented
    by the additional permissions listed below.

    You should have received a copy of the GNU Lesser General Public License
    along with ParScale. If not, see <http://www.gnu.org/licenses/lgpl.html>.

	This code is designed to simulate transport processes (e.g., for heat and
	mass) within porous and no-porous particles, eventually undergoing
	chemical reactions.

	Parts of the code were developed in the frame of the NanoSim project funded
	by the European Commission through FP7 Grant agreement no. 604656.
\*-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
Description
	This class is the base class for all physical sub-models (e.g., for properties),
	as well as overall particle model equations (e.g., for transient heat conduction
	inside the particle).
-----------------------------------------------------------------------------------*/

#ifndef PASC_MODEL_BASE_H
#define PASC_MODEL_BASE_H

#include "pascal_base_accessible.h"
#include "string.h"

#define __PIC__
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QString>
#include <QtCore/QFile>

namespace PASCAL_NS
{

//numbering of equation type
enum{ HEAT,		//0
      SPECIES,	//1
      OTHER,    //2
      REACTION  //3
    };


class ModelBase : public ParScaleBaseAccessible
{
    public:

      ModelBase(ParScale *ptr,const char *_name);
      ~ModelBase();

      virtual void init(int narg, char const* const* arg) {};

      virtual void begin_of_step() {};
      virtual void pre_middle_of_step() {};
      virtual void post_middle_of_step() {};
      virtual void end_of_step() {};


      //Access functions
      const char* name() {return name_;}
      const char* scope() {  return scope_; }
      virtual double value(){return 0.0;};
		
	  void readQJsonObject(const QJsonObject &json);
  	  void lookup_constant_in_QJsonObject(const QJsonObject &json, double *constant_value, const char *constant_name);
	  void read_model_json_file(const char *model_name,double * ptr);

	  void readQJsonConstant(const QJsonObject &json,const char *name_model,double * ptr) ;

      QJsonObject readQJsonObject(const char* filename, const char *object_name);
      void read_verbose_json_file(const char *property_name, bool *ptr);
      void read_species_properties(const char *species_name, const char *property_name, double *ptr);
      void read_chemistry_single_react_json_file(const char *model_name,double * ptr);
      void read_chemistry_single_react_json_file(const char *model_name,bool * ptr);

	  mutable QJsonObject global_properties;
	  mutable QJsonDocument  loadDoc;
	  mutable QString        myName;
	  mutable QString 		 specific_model_name;
	  mutable QJsonValue 	 QJvalue_;
  	  mutable QString        model_constant_;

    private:

      char *name_;
      char *scope_; // scope/name for JSON file

	//model constants
	
};

} //end PASCAL_NS

#endif

