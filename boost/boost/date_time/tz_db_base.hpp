#ifndef DATE_TIME_TZ_DB_BASE_HPP__
#define DATE_TIME_TZ_DB_BASE_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/shared_ptr.hpp"
#include "boost/date_time/time_zone_names.hpp"
#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/tokenizer.hpp"
#include <string>
#include <map>
#include <stdexcept>
#include <fstream>
#include <iostream> // debugging -- TODO remove

namespace boost {
  namespace date_time {


    struct data_not_accessible : public std::logic_error
    {
      data_not_accessible() : std::logic_error(std::string("Unable to locate or access the required datafile to construct this class.")) {}
      data_not_accessible(const std::string& filespec) : std::logic_error(std::string("Unable to locate or access the required datafile. Filespec: " + filespec)) {}
    };
 
    template<class time_zone_type, class rule_type>
    class tz_db_base {
    public:
      /* Having charT as a template parameter created problems 
       * with posix_time::duration_from_string. Templatizing 
       * duration_from_string was not possible at this time, however, 
       * it should be possible in the future (when poor compilers get 
       * fixed or stop being used). 
       * Since this class was designed to use charT as a parameter it 
       * is simply typedefed here to ease converting in back to a 
       * parameter the future */
      typedef char charT;

      typedef typename time_zone_type::base_type time_zone_base_type;
      typedef typename time_zone_type::time_duration_type time_duration_type;
      typedef time_zone_names<charT> time_zone_names;
      typedef dst_adjustment_offsets<time_duration_type> dst_adjustment_offsets;
      typedef std::basic_string<charT> string_type;

      //! Constructs an empty database
      tz_db_base() {}

      //! Process csv data file, may throw "local_time::data_not_accessible"
      void load_from_file(const std::string& pathspec) throw(data_not_accessible)
      {
        string_type in_str;
        std::string  buff;
        
        std::ifstream ifs(pathspec.c_str());
        if(!ifs){
          throw data_not_accessible(pathspec);
        }
        getline(ifs, buff); // first line is column headings

        while( getline(ifs, buff)) {
          parse_string(buff);
        }
      }

      //! returns true if record successfully added to map
      /*! Takes an id string in the form of "America/Phoenix", and a 
       * time_zone object for that region. The id string must be a unique 
       * name that does not already exist in the database. */
      bool add_record(const string_type& id, 
                      boost::shared_ptr<time_zone_base_type> tz)
      {
        typename map_type::value_type p(id, tz); 
        return (m_zone_map.insert(p)).second;
      }

      //! Returns a time_zone object built from the specs for the given region
      /*! Returns a time_zone object built from the specs for the given 
       * region. If region does not exist a local_time::record_not_found 
       * exception will be thrown */
      boost::shared_ptr<time_zone_base_type> 
      time_zone_from_region(const string_type& region) const 
      {
        // get the record
        typename map_type::const_iterator record = m_zone_map.find(region);
        if(record == m_zone_map.end()){
          return boost::shared_ptr<time_zone_base_type>(); //null pointer
        }
        return record->second;
      }
    
    private:
      typedef std::map<string_type, boost::shared_ptr<time_zone_base_type> > map_type;
      map_type m_zone_map;

      // start and end rule are of the same type
      typedef typename rule_type::start_rule::week_num week_num;

      /* TODO: mechanisms need to be put in place to handle different
       * types of rule specs. parse_rules() only handles nth_kday
       * rule types. */
      
      //! parses rule specs for transition day rules
      rule_type* parse_rules(const string_type& sr, const string_type& er) const
      {
        using namespace gregorian;
        // start and end rule are of the same type, 
        // both are included here for readability
        typedef typename rule_type::start_rule start_rule;
        typedef typename rule_type::end_rule end_rule;
       
        // these are: [start|end] nth, day, month
        int s_nth = 0, s_d = 0, s_m = 0;
        int e_nth = 0, e_d = 0, e_m = 0;
        split_rule_spec(s_nth, s_d, s_m, sr);
        split_rule_spec(e_nth, e_d, e_m, er);
        
        typename start_rule::week_num s_wn, e_wn;
        s_wn = get_week_num(s_nth);
        e_wn = get_week_num(e_nth);
        
        
        return new rule_type(start_rule(s_wn, s_d, s_m),
                             end_rule(e_wn, e_d, e_m));
      }
      //! helper function for parse_rules()
      week_num get_week_num(int nth) const
      {
        typedef typename rule_type::start_rule start_rule;
        switch(nth){
        case 1:
          return start_rule::first;
        case 2:
          return start_rule::second;
        case 3:
          return start_rule::third;
        case 4:
          return start_rule::fourth;
        case 5:
        case -1:
          return start_rule::fifth;
        default:
          // shouldn't get here - add error handling later
          break;
        }
        return start_rule::fifth; // silence warnings
      }
          
      //! splits the [start|end]_date_rule string into 3 ints
      void split_rule_spec(int& nth, int& d, int& m, string_type rule) const
      {
        typedef boost::tokenizer<boost::char_separator<charT>,
          string_type::const_iterator,
          string_type > tokenizer;
        const charT sep_char[] = { ';', '\0'};
        boost::char_separator<charT> sep(sep_char);
        tokenizer tokens(rule, sep); // 3 fields
        
        typename tokenizer::iterator tok_iter = tokens.begin(); 
        nth = atoi(tok_iter->c_str()); ++tok_iter;
        d   = atoi(tok_iter->c_str()); ++tok_iter;
        m   = atoi(tok_iter->c_str());
      }

     
      //! Take a line from the csv, turn it into a time_zone_type.
      /*! Take a line from the csv, turn it into a time_zone_type,
       * and add it to the map. Zone_specs in csv file are expected to 
       * have eleven fields that describe the time zone. Returns true if 
       * zone_spec successfully added to database */
      bool parse_string(string_type& s)
      {
        
        std::vector<string_type> result;
        typedef boost::token_iterator_generator<boost::escaped_list_separator<charT> >::type token_iter_type;
        token_iter_type i = boost::make_token_iterator<string_type>(s.begin(),
                                                                    s.end(),boost::escaped_list_separator<charT>());
        token_iter_type end;
        while (i != end) {
          result.push_back(*i);
          i++;
        }

        enum db_fields { ID, STDABBR, STDNAME, DSTABBR, DSTNAME, GMTOFFSET,
                         DSTADJUST, START_DATE_RULE, START_TIME, END_DATE_RULE,
                         END_TIME };

        if (result.size() != END_TIME) { 
          //TODO throw exception because number of fields is wrong 
          //something like 'Expecting 13 fields, got ' result.size() fields
          // in line (add the line that is wrong here).
        }

        // initializations
        bool has_dst = true; 
        if(result[DSTABBR] == std::string()){
          has_dst = false;
        }


        // start building components of a time_zone
        time_zone_names names(result[STDNAME], result[STDABBR],
                              result[DSTNAME], result[DSTABBR]);

        time_duration_type utc_offset = 
          posix_time::duration_from_string(result[GMTOFFSET]);
        
        dst_adjustment_offsets adjust(time_duration_type(0,0,0),
                                      time_duration_type(0,0,0),
                                      time_duration_type(0,0,0));

        boost::shared_ptr<rule_type> rules;

        if(has_dst){
          adjust = dst_adjustment_offsets(
                                          posix_time::duration_from_string(result[DSTADJUST]),
                                          posix_time::duration_from_string(result[START_TIME]),
                                          posix_time::duration_from_string(result[END_TIME])
                                          );

          rules = 
            boost::shared_ptr<rule_type>(parse_rules(result[START_DATE_RULE],
                                                     result[END_DATE_RULE]));
        }
        string_type id(result[ID]);
        boost::shared_ptr<time_zone_base_type> zone(new time_zone_type(names, utc_offset, adjust, rules));
        return (add_record(id, zone));
        
      } 
     
    };

} } // namespace

#endif // DATE_TIME_TZ_DB_BASE_HPP__
